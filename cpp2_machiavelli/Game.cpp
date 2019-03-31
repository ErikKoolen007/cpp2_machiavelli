#include "Game.h"
#include "SetupRoundState.h"
#include "GameRoundState.h"
#include "GameEndState.h"
#include "PreGameState.h"

Game::Game()
{
	state_machine_ = std::make_unique<state_machine<Game>>(*this);
	state_machine_->addState(std::make_unique<PreGameState>());
	state_machine_->addState(std::make_unique<SetupRoundState>());
	state_machine_->addState(std::make_unique<GameRoundState>());
	state_machine_->addState(std::make_unique<GameEndState>());
	state_machine_->set_current_state("PreGameState");

	game_manager_ = std::make_unique<GameManager>(*state_machine_);
}

void Game::handle_command(ClientInfo& client_info, const std::string& command)
{
	state_machine_->handle_input(client_info, command);
}
