#pragma once
#include "GameState.h"
#include "FileReader.h"

class SetupState :
	public GameState
{
public:
	SetupState(GameManager& manager) : GameState(manager)
	{
		file_reader_ = std::make_unique<FileReader>();
		//prepare the game 
		SetupState::setup();
	}

	void next() override;

	void setup() override;
private:
	//InGameState nextState;
	std::unique_ptr<FileReader> file_reader_;
	std::unique_ptr<std::deque<BuildingCard>> building_cards_;
	std::unique_ptr<std::deque<CharacterCard>> character_cards_;
};
