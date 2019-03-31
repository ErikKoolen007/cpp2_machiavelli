#pragma once
#include "ClientInputHandler.h"
#include "ClientInfo.h"

class GameManager
{
public:
	GameManager()
	{
		handler_ = std::make_unique<ClientInputHandler>();
	}

	ClientInputHandler& get_client_input_handler() const;
	void add_client(const std::shared_ptr<ClientInfo>& client);
	void remove_client(ClientInfo& client);
	std::vector<std::shared_ptr<ClientInfo>>& get_clients() { return current_clients_; }
	void notify_all_players(std::string message);

	void handle_command(ClientInfo& client_info, const std::string& command) { handler_->handleInput(client_info, command); }

private:
	std::unique_ptr<ClientInputHandler> handler_;
	std::vector<std::shared_ptr<ClientInfo>> current_clients_;
	int last_player_id_ = 0;
};

