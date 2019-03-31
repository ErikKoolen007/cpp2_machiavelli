#pragma once
#include "State.h"
#include "Game.h"

class PreGameState : public State<Game>
{
public:
	PreGameState() = default;
	void on_enter(Game& game) override;
	void handle_input(Game& game, ClientInfo& client_info, const std::string& command) override;
	void on_exit(Game& game) override;
	std::string name() override;
};

