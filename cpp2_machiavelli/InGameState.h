#pragma once
#include "GameState.h"
#include "Turn.h"
#include <stack>
#include "EndState.h"

class InGameState :	public GameState
{
public:
	Turn setupFirstTurn();
	void next() override;
private:
	//std::deque<Turn> turns;
	//EndState nextState;
};

