#pragma once
#include "State.h"
#include "Game.h"

class CondottiereState : public State<Game>
{
public:
	CondottiereState() = default;

	void on_enter(Game& game) override;
	void handle_input(Game& game, ClientInfo& client, const std::string& command) override;
	void on_exit(Game& game) override;
	std::string name() override;

private:
	int building_option_count_{ 0 };
	std::unordered_map<int, int> option_map_{};
};

