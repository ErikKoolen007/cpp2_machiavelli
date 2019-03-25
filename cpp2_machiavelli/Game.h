#pragma once
#include "GameState.h"
#include "GameManager.h"
#include <memory>
#include <thread>
#include <vector>

class Game
{
public:
	Game(std::vector<std::thread>& clients, std::unique_ptr<GameManager> manager, std::unique_ptr<GameState> state) 
	: clients(clients), manager(std::move(manager)), state(std::move(state))
	{
	}

private:
	std::vector<std::thread>& clients;
	std::unique_ptr<GameManager> manager;
	std::unique_ptr<GameState> state;
};

