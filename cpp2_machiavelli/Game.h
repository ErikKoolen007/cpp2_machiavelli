#pragma once
#include "GameState.h"
#include "GameManager.h"
#include <memory>
#include <thread>
#include <vector>
#include "SetupState.h"

class Game
{
public:
	Game(std::vector<std::thread>& clients)
	{
		manager = std::make_unique<GameManager>(clients);
		state = std::make_unique<SetupState>(*manager);
	}

private:
	std::unique_ptr<GameManager> manager;
	std::unique_ptr<GameState> state;
};

