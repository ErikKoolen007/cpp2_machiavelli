#pragma once
#include "GameManager.h"

//is abstract
class GameState
{
public:
	GameState(GameManager& manager) : manager(manager) {}
	virtual void next() = 0;
protected:
	GameManager& manager;
};

