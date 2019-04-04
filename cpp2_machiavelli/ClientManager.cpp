#include "ClientManager.h"
#include <algorithm>

void ClientManager::add_client(const std::shared_ptr<ClientInfo>& client)
{
	auto &socket = client->get_socket();
	auto &player = client->get_player();

	last_player_id_++;
	player.id(last_player_id_);
	current_clients_.push_back(client);

	const auto message = "Player (" + player.get_name() + ": " + std::to_string(player.id())
		+ ") joined! Current player count = " + std::to_string(current_clients_.size()) + "\r\n";

	std::cout << message;
	notify_all_players("Server: " + message);

	socket.write("Welcome, " + player.get_name() + ", have fun playing our game!\r\n");

	if (current_clients_.size() > 1)
	{
		//Start game with setup round
		state_machine_.change_state("SetupRoundState");
	}
	else
	{
		socket.write("The game will begin when another player joins.\r\n");
	}
}

void ClientManager::remove_client(ClientInfo& client)
{
	current_clients_.erase(
		std::remove_if(current_clients_.begin(), current_clients_.end(),
			[&client](auto const &ptr) {return &client == ptr.get(); }),
		current_clients_.end()
	);

	std::cout << "Player (" << client.get_player().get_name() << ": " << client.get_player().id()
		<< ") left! Current player count = " << current_clients_.size() << "\n";
}

void ClientManager::notify_all_players(std::string message)
{
	std::for_each(current_clients_.begin(), current_clients_.end(), [&](auto& client)
	{
		client->get_socket().write(message);
	});
}

void ClientManager::notify_player(std::string message, int player_id)
{
	std::for_each(current_clients_.begin(), current_clients_.end(), [&](auto& client)
	{
		if (client->get_player().id() == player_id)
		{
			client->get_socket().write(message + "\r\n");
		}
	});
}
