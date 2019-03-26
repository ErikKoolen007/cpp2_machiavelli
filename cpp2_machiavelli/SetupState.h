#pragma once
#include "GameState.h"
#include "InGameState.h"
#include "FileReader.h"

class SetupState :
	public GameState
{
public:
	SetupState(GameManager& manager) : GameState(manager)
	{
		fileReader = std::make_unique<FileReader>();
	}
	void next() override;
private:
	//InGameState nextState;
	std::unique_ptr<FileReader> fileReader;
};

