#pragma once
#include "ClientInputHandler.h"
#include "ClientInfo.h"

class GameManager
{
public:
	GameManager()
	{
		handler = std::make_unique<ClientInputHandler>();
	}

	ClientInputHandler& getClientInputHandler() const;
	void add_client(const std::shared_ptr<ClientInfo>& client);
	std::vector<std::shared_ptr<ClientInfo>>& get_clients() { return current_clients_; }
	void handle_command(ClientInfo& client_info, const std::string& command) { handler->handleInput(client_info, command); }

private:
	std::unique_ptr<ClientInputHandler> handler;
	std::vector<std::shared_ptr<ClientInfo>> current_clients_;
	int lastPlayerId = 0;
};

