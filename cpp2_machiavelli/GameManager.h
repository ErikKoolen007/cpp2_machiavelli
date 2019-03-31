#pragma once
#include "ClientManager.h"
#include "ClientInfo.h"
#include "state_machine.h"

class Game;

class GameManager
{
public:
	GameManager(state_machine<Game>& state_machine) : state_machine_(state_machine)
	{
	}

private:
	state_machine<Game>& state_machine_;
};

