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
		std::shared_ptr<CharacterCard>& current_character) const;
	static std::string generate_help_msg();
	static void handle_build_building();
	std::unordered_map<int, BuildingCard&> option_map_;
	int buildings_built_ = 0;
	bool building_coins_used_ = false;
	bool building_ = false;
	bool king_killed_ = false;
	int player_id_ = 999;
	int character_id_ = 999;
	bool setup_round_state_triggered_ = false;
	void end_turn(Game& game);
};

