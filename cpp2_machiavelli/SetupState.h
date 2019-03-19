#pragma once
#include "GameState.h"
#include "InGameState.h"
#include "FileReader.h"

class SetupState :
	public GameState
{
public:
private:
	InGameState next;
	FileReader fileReader;
};

