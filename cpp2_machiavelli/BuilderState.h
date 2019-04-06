#pragma once
#include "State.h"
#include "Game.h"

class BuilderState : public State<Game>
{
public:
	BuilderState() = default;

	void on_enter(Game& game) override;
	void handle_input(Game& game, ClientInfo& client, const std::string& command) override;
	void on_exit(Game& game) override;
	std::string name() override;
};

