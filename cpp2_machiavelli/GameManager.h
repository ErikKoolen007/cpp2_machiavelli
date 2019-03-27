#pragma once
#include "ClientInputHandler.h"

class GameManager
{
public:
	GameManager(std::vector<std::thread>& clients)
	{
		handler = std::make_unique<ClientInputHandler>(clients);
	}

	ClientInputHandler& getClientInputHandler() const;

private:
	std::unique_ptr<ClientInputHandler> handler;
};

