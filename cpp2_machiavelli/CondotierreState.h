#pragma once
#include "State.h"
#include "Game.h"

class CondotierreState : public State<Game>
{
public:
	CondotierreState() = default;

	void on_enter(Game& game) override;
	void handle_input(Game& game, ClientInfo& client, const std::string& command) override;
	void on_exit(Game& game) override;
	std::string name() override;
};

