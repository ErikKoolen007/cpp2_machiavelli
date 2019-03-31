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
	//InGameState nextState;
	//std::unique_ptr<FileReader> file_reader_;
	//std::unique_ptr<std::deque<BuildingCard>> building_cards_;
	//std::unique_ptr<std::deque<CharacterCard>> character_cards_;
};
