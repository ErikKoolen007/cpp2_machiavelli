#pragma once
#include "ClientInputHandler.h"
#include "ClientInfo.h"
#include "state_machine.h"

class Game;

class GameManager
{
public:
	GameManager(state_machine<Game>& state_machine) : state_machine_(state_machine)
	{
		handler_ = std::make_unique<ClientInputHandler>();
	}

	ClientInputHandler& get_client_input_handler() const;
	void add_client(const std::shared_ptr<ClientInfo>& client);
	void remove_client(ClientInfo& client);
	std::vector<std::shared_ptr<ClientInfo>>& get_clients() { return current_clients_; }
	void notify_all_players(std::string message);

private:
	std::unique_ptr<ClientInputHandler> handler_;
	state_machine<Game>& state_machine_;
	std::vector<std::shared_ptr<ClientInfo>> current_clients_;
	int last_player_id_ = 0;
};

