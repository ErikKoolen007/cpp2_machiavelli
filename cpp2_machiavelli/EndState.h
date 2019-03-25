#pragma once
#include "GameState.h"
#include "SetupState.h"

class EndState : public GameState
{
public:
	void next() override;
private:
	//SetupState nextState;
};

