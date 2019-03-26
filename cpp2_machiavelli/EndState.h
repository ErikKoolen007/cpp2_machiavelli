#pragma once
#include "GameState.h"
#include "SetupState.h"

class EndState : public GameState
{
public:
	void next() override;
	void setup() override;
private:
	//SetupState nextState;
};

