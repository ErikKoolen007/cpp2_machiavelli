#pragma once
#include "GameState.h"
#include "GameManager.h"
#include <memory>
#include <vector>
#include "SetupState.h"

class Game
{
public:
	Game()
	{
		manager_ = std::make_unique<GameManager>();
		state = std::make_unique<SetupState>(*manager_);
	}

	GameManager& get_manager() { return *manager_; }
	
private:
	std::unique_ptr<GameManager> manager_;
	std::unique_ptr<GameState> state;
};

