#pragma once
#include "ClientInputHandler.h"

class GameManager
{
public:
	GameManager(std::vector<std::thread>& clients)
	{
		handler = std::make_unique<ClientInputHandler>(clients);
	}
private:
	std::unique_ptr<ClientInputHandler> handler;
};

