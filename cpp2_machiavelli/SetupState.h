#pragma once
#include "GameState.h"
#include "InGameState.h"
#include "FileReader.h"

class SetupState :
	public GameState
{
public:
	SetupState(GameManager& manager) : GameState(manager) {}
	void next() override;
private:
	//InGameState nextState;
	//FileReader fileReader;
};

