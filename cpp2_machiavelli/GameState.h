#pragma once
#include "GameManager.h"

//is abstract
class GameState
{
public:
	virtual ~GameState() = default;
	GameState(GameManager& manager) : manager(manager) {}
	virtual void next() = 0;
	virtual void setup() = 0;
protected:
	GameManager& manager;
};

