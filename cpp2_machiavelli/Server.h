#pragma once
#include "ClientInfo.h"
#include "Sync_queue.h"
#include "ClientCommand.h"

class Server
{
public:
	Server() = default;

	void consume_command();
	std::shared_ptr<ClientInfo> init_client_session(Socket client);
	void handle_client(Socket client);
	void init();

private:
	const int tcp_port_{ 1080 };
	const std::string prompt_{ "machiavelli> " };
	bool running_ = true;
	Sync_queue<ClientCommand> queue_;

};

