#pragma once
#include "GameState.h"
#include "FileReader.h"

class SetupState :
	public GameState
{
public:
	SetupState(GameManager& manager) : GameState(manager)
	{
		fileReader = std::make_unique<FileReader>();
		//prepare the game 
		setup();
	}

	void next() override;

	void setup() override;
private:
	//InGameState nextState;
	std::unique_ptr<FileReader> fileReader;
	std::unique_ptr<std::deque<BuildingCard>> buildingCards;
	std::unique_ptr<std::deque<CharacterCard>> characterCards;
};
