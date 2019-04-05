#pragma once
#include "State.h"
#include "Game.h"

class SetupRoundState : public State<Game>
{
public:
	SetupRoundState() = default;

	void on_enter(Game& game) override;
	void handle_input(Game& game, ClientInfo& client_info, const std::string& command) override;
	void on_exit(Game& game) override;
	std::string name() override;
	
private:
	void draw_characters(int player_id, Game& game);
	void add_starting_resources(Game& game);
};
