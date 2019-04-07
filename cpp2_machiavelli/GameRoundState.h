#pragma once
#include "State.h"
#include "Game.h"

class GameRoundState :	public State<Game>
{
public:
	GameRoundState() = default;

	void on_enter(Game& game) override;
	void handle_input(Game& game, ClientInfo& client_info, const std::string& command) override;
	void on_exit(Game& game) override;
	std::string name() override;
private:
	std::string generate_options_msg(
		std::shared_ptr<CharacterCard>& current_character);
	int buildings_built = 0;
	bool building_coins_used = false;
};

