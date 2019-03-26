//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Revised by Jeroen de Haas on 22/11/2016
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
#include <chrono>

#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "Player.h"
#include "ClientInfo.h"
#include "FileReader.h"
#include "Game.h"

namespace machiavelli {
    const int tcp_port {1080};
	
	//cause memory leak block 154
    const std::string prompt {"machiavelli> "};
}

static bool running = true;

//causes memory leak block 155 and 156
static Sync_queue<ClientCommand> queue;

void consume_command() // runs in its own thread
{
    try {
        while (running) {
            ClientCommand command {queue.get()}; // will block here unless there are still command objects in the queue
            if (auto clientInfo = command.get_client_info().lock()) {
                auto &client = clientInfo->get_socket();
                auto &player = clientInfo->get_player();
                try {
                    // TODO handle command here
					if(command.get_cmd() == "card")
					{
						//BuildingCard testCard{ "Test", 2, "Geel" };
						//std::cout << testCard << std::endl;
						//client << "Gebouwen:\n" << testCard.to_string() << "\n";
						FileReader file_reader;
						file_reader.load_building_cards();
					}
                    client << player.get_name() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n" << machiavelli::prompt;
                } catch (const std::exception& ex) {
	                std::cerr << "*** exception in consumer thread for player " << player.get_name() << ": " << ex.what() << '\n';
                    if (client.is_open()) {
                        client.write("Sorry, something went wrong during handling of your request.\r\n");
                    }
                } catch (...) {
	                std::cerr << "*** exception in consumer thread for player " << player.get_name() << '\n';
                    if (client.is_open()) {
                        client.write("Sorry, something went wrong during handling of your request.\r\n");
                    }
                }
            }
        }
    } catch (...) {
	    std::cerr << "consume_command crashed\n";
    }
}

std::shared_ptr<ClientInfo> init_client_session(Socket client) {
    client.write("Welcome to Server 1.0! To quit, type 'quit'.\r\n");
    client.write("What's your name?\r\n");
    client.write(machiavelli::prompt);
	std::string name;
    bool done { false };
    while(!done) {
        done = client.readline([&name](std::string input) {
            name = input;
        });
    }
    return std::make_shared<ClientInfo>(std::move(client), Player { name });
}

void handle_client(Socket client) // this function runs in a separate thread
{

	//move to game
    try {
        auto client_info = init_client_session(std::move(client));
        auto &socket = client_info->get_socket();
        auto &player = client_info->get_player();
        socket << "Welcome, " << player.get_name() << ", have fun playing our game!\r\n" << machiavelli::prompt;

        while (running) { // game loop
            try {
                // read first line of request
                std::string cmd;
                if (socket.readline([&cmd](std::string input) { cmd=input; })) {
	                std::cerr << '[' << socket.get_dotted_ip() << " (" << socket.get_socket() << ") " << player.get_name() << "] " << cmd << "\r\n";

					//move
                    if (cmd == "quit") {
                        socket.write("Bye!\r\n");
                        break; // out of game loop, will end this thread and close connection
                    }
					//move
                    else if (cmd == "quit_server") {
                        running = false;
                    }

                    ClientCommand command {cmd, client_info};
                    queue.put(command);
                };

            } catch (const std::exception& ex) {
                socket << "ERROR: " << ex.what() << "\r\n";
            } catch (...) {
                socket.write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
            }
        }
    } 
    catch(std::exception &ex) {
	    std::cerr << "handle_client " << ex.what() << "\n";
    }
    catch (...) {
	    std::cerr << "handle_client crashed\n";
    }
}

int main(int argc, const char * argv[])
{
	//_CrtSetBreakAlloc(157);
	//new int();

	if (true) {
		// start command consumer thread
		std::vector<std::thread> all_threads;
		all_threads.emplace_back(consume_command);
		
		// create a server socket
		ServerSocket server{ machiavelli::tcp_port };

	//create the game
	std::unique_ptr<Game> game = std::make_unique<Game>(all_threads);

    try {
	    std::cerr << "server listening" << '\n';
        while (running) {
            // wait for connection from client; will create new socket
            server.accept([&all_threads](Socket client) {
                std::cerr << "Connection accepted from " << client.get_dotted_ip() << "\n";
                all_threads.emplace_back(handle_client, std::move(client));
            });
	        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } catch (const std::exception& ex) {
	    std::cerr << ex.what() << ", resuming..." << '\n';
    } catch (...) {
	    std::cerr << "problems, problems, but: keep calm and carry on!\n";
    }

		for (auto &t : all_threads) {
			t.join();
		}
	}

	//Memory check
	std::cout << "\nMemory leaks? (0 for no, 1 for yes. See output for details.)" << _CrtDumpMemoryLeaks() << std::endl;

    return 0;
}

