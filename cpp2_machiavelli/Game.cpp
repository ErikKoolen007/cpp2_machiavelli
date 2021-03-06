#include "Game.h"
#include "SetupRoundState.h"
#include "GameRoundState.h"
#include "GameEndState.h"
#include "PreGameState.h"
#include "AssassinState.h"
#include "BuilderState.h"
#include "CondottiereState.h"
#include "KingState.h"
#include "MageState.h"
#include "MerchantState.h"
#include "PreacherState.h"
#include "ThiefState.h"

Game::Game()
{
	state_machine_ = std::make_unique<StateMachine<Game>>(*this);
	state_machine_->addState(std::make_unique<PreGameState>());
	state_machine_->addState(std::make_unique<SetupRoundState>());
	state_machine_->addState(std::make_unique<GameRoundState>());
	state_machine_->addState(std::make_unique<GameEndState>());

	state_machine_->addState(std::make_unique<AssassinState>());
	state_machine_->addState(std::make_unique<BuilderState>());
	state_machine_->addState(std::make_unique<CondottiereState>());
	state_machine_->addState(std::make_unique<KingState>());
	state_machine_->addState(std::make_unique<MageState>());
	state_machine_->addState(std::make_unique<MerchantState>());
	state_machine_->addState(std::make_unique<PreacherState>());
	state_machine_->addState(std::make_unique<ThiefState>());
	state_machine_->set_current_state("PreGameState");

	game_manager_ = std::make_unique<GameManager>(*state_machine_);
	client_manager_ = std::make_unique<ClientManager>(*state_machine_);
	character_manager_ = std::make_unique<CharacterManager>(*client_manager_);
}

void Game::handle_command(ClientInfo& client_info, const std::string& command) const
{
	if(client_info.locked())
	{
		client_manager().notify_player("\r\nHey, your are playing out of turn, please wait until it's your turn \r\n", 
			client_info.get_player().id());
	} else
	{
		state_machine_->handle_input(client_info, command);
	}
}
