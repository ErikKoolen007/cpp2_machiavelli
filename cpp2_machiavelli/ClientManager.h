#pragma once
#include <string>
#include "ClientInfo.h"
#include "StateMachine.h"

class Game;

class ClientManager
{
public:
	ClientManager(StateMachine<Game>& state_machine) : state_machine_(state_machine)
	{
	}

	void add_client(std::shared_ptr<ClientInfo>& client);
	void remove_client(ClientInfo& client);
	ClientInfo& get_client(int player_id);
	int get_client_count() const { return current_clients_.size(); }
	std::vector<std::shared_ptr<ClientInfo>>& get_clients() { return current_clients_; }
	ClientInfo& get_next_client(int current_client_id);
	void notify_all_players(std::string message);
	void notify_player(std::string message, int player_id);
	void lock_client(int player_id, bool lock);
	void lock_all_clients();

private:
	StateMachine<Game>& state_machine_;
	std::vector<std::shared_ptr<ClientInfo>> current_clients_;
	int last_player_id_ = 0;
};

