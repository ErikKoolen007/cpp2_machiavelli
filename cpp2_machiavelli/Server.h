#pragma once
#include "ClientInfo.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "Game.h"

class Server
{
public:
	Server()
	{
		game_ = std::make_unique<Game>();
	}

	void consume_command();
	std::shared_ptr<ClientInfo> init_client_session(Socket client);
	void handle_client(Socket client);
	void init();

private:
	const int tcp_port_{ 1080 };
	const std::string prompt_{ "machiavelli> " };
	bool running_ = true;
	Sync_queue<ClientCommand> queue_;
	std::unique_ptr<Game> game_;
};

