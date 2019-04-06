#pragma once
#include "State.h"
#include "Game.h"

class ThiefState : public State<Game>
{
public:
	ThiefState() = default;

	void on_enter(Game& game) override;
	void handle_input(Game& game, ClientInfo& client, const std::string& command) override;
	void on_exit(Game& game) override;
	std::string name() override;

private:
	bool stole_from_dead_character_{ false };

	static void print_target_options(Socket& socket);
};

