//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Revised by Jeroen de Haas on 22/11/2016
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Server.h"
#include "FileReader.h"

void Server::consume_command() // runs in its own thread
{
	try {
		while (running_) {
			ClientCommand command{queue_.get() }; // will block here unless there are still command objects in the queue
			if (auto clientInfo = command.get_client_info().lock()) {
				auto &client = clientInfo->get_socket();
				auto &player = clientInfo->get_player();
				try {
					// TODO handle command here
					game_->handle_command(*clientInfo, command.get_cmd());
					//if (command.get_cmd() == "card")
					//{
					//	//BuildingCard testCard{ "Test", 2, "Geel" };
					//	//std::cout << testCard << std::endl;
					//	//client << "Gebouwen:\n" << testCard.to_string() << "\n";
					//	FileReader file_reader;
					//	file_reader.load_building_cards();
					//}
					
				}
				catch (const std::exception& ex) {
					std::cerr << "*** exception in consumer thread for player " << player.get_name() << ": " << ex.what() << '\n';
					if (client.is_open()) {
						client.write("Sorry, something went wrong during handling of your request.\r\n");
					}
				}
				catch (...) {
					std::cerr << "*** exception in consumer thread for player " << player.get_name() << '\n';
					if (client.is_open()) {
						client.write("Sorry, something went wrong during handling of your request.\r\n");
					}
				}
			}
		}
	}
	catch (...) {
		std::cerr << "consume_command crashed\n";
	}
}

std::shared_ptr<ClientInfo> Server::init_client_session(Socket client) {
	client.write("Welcome to Server 1.0! To quit, type 'quit'.\r\n");
	client.write("What's your name?\r\n");
	client.write(prompt_);
	std::string name;
	bool done{ false };
	while (!done) {
		done = client.readline([&name](std::string input) {
			name = input;
		});
	}
	return std::make_shared<ClientInfo>(std::move(client), Player{ name });
}

void Server::handle_client(Socket client) // this function runs in a separate thread
{
	try {
		auto client_info = init_client_session(std::move(client));
		auto &socket = client_info->get_socket();
		auto &player = client_info->get_player();

		if(game_->client_manager().get_client_count() >= 2 )
		{
			socket.write("Sorry the game is full, please try again later. \r\nYou will now be disconnected. Bye!\r\n");
		}
		else {
			game_->client_manager().add_client(client_info);

			while (running_) { // game loop
				try {
					// read first line of request
					std::string cmd;
					if (socket.readline([&cmd](std::string input) { cmd = input; })) {
						std::cerr << '[' << socket.get_dotted_ip() << " (" << socket.get_socket() << ") " << player.get_name() << "] " << cmd << "\r\n";

						if (cmd == "quit") {
							socket.write("Bye!\r\n");
							const int previous_player_count = game_->client_manager().get_client_count();

							game_->client_manager().remove_client(*client_info);
							if (previous_player_count == 2)
							{
								const std::string message = player.get_name() + " left. Game now has insufficient players and will terminate. \r\n";
								game_->client_manager().notify_all_players(message);
								game_->state_machine().change_state("PreGameState");
							}
							
							break; // out of game loop, will end this thread and close connection
						}
						else if (cmd == "quit_server") {
							running_ = false;
						}

						ClientCommand command{ cmd, client_info };
						queue_.put(command);
					};

				}
				catch (const std::exception& ex) {
					socket << "ERROR: " << ex.what() << "\r\n";
				}
				catch (...) {
					socket.write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
				}
			}
		}
	}
	catch (std::exception &ex) {
		std::cerr << "handle_client " << ex.what() << "\n";
	}
	catch (...) {
		std::cerr << "handle_client crashed\n";
	}
}

void Server::init()
{
	// start command consumer thread
	std::vector<std::thread> all_threads;
	all_threads.emplace_back(&Server::consume_command, this);

	// create a server socket
	ServerSocket server{ tcp_port_ };

	try {
		std::cerr << "server listening" << '\n';
		while (running_) {
			// wait for connection from client; will create new socket
			server.accept([&all_threads, this](Socket client) {
				std::cerr << "Connection accepted from " << client.get_dotted_ip() << "\n";
				all_threads.emplace_back(&Server::handle_client, this, std::move(client));
			});
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << ", resuming..." << '\n';
	}
	catch (...) {
		std::cerr << "problems, problems, but: keep calm and carry on!\n";
	}

	for (auto &t : all_threads) {
		t.join();
	}
}
