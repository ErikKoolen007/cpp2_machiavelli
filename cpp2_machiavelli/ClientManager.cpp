#include "ClientManager.h"
#include <algorithm>


void ClientManager::add_client(std::shared_ptr<ClientInfo>& client)
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

ClientInfo& ClientManager::get_client(int player_id)
{
	return **std::find_if(current_clients_.begin(), current_clients_.end(), 
									[&](auto& client) { return client->get_player().id() == player_id;});
}

ClientInfo& ClientManager::get_king()
{
	return **std::find_if(get_clients().begin(), get_clients().end(),
		[&](std::shared_ptr<ClientInfo>& client_ptr) {return client_ptr->get_player().king(); });
}

ClientInfo& ClientManager::get_current_client()
{
	return **std::find_if_not(current_clients_.begin(), current_clients_.end(),
		[&](std::shared_ptr<ClientInfo>& client) { return client->locked(); });
}

ClientInfo& ClientManager::get_next_client(int current_client_id)
{
	return **std::find_if(current_clients_.begin(), current_clients_.end(), 
		[&](std::shared_ptr<ClientInfo>& client){ return client->get_player().id() != current_client_id; });
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

void ClientManager::lock_client(int player_id, bool lock)
{
	get_client(player_id).locked(lock);
}

void ClientManager::lock_all_clients()
{
	std::for_each(current_clients_.begin(), current_clients_.end(), [&](auto& client)
	{
		client->locked(true);
	});
}

void ClientManager::trigger_next_state(std::string new_state)
{
	this->state_machine_.change_state(new_state);
}

void ClientManager::clear_characters_of_players()
{
	std::for_each(current_clients_.begin(), current_clients_.end(), [&](auto& client) {client->get_player().clear_characters(); });
}

std::map<int, int> ClientManager::get_round_routing_table()
{
	std::map<int, int> routing_table;
	std::for_each(current_clients_.begin(), current_clients_.end(), [&](auto& client)
	{
		std::vector<std::shared_ptr<CharacterCard>>& player_characters = client->get_player().character_cards();
		std::for_each(player_characters.begin(), player_characters.end(), [&](auto& character) {
			routing_table.insert(std::make_pair(character->id(), client->get_player().id()));
		});
	});
	return routing_table;
}
