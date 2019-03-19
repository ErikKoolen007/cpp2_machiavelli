#pragma once
#include "GameState.h"
#include "Turn.h"
#include <stack>
#include "EndState.h"

class InGameState :	public GameState
{
public:
	Turn setupFirstTurn();
private:
	std::deque<Turn> turns;
	EndState next;
};

