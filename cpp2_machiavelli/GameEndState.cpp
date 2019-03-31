#include "GameEndState.h"

void GameEndState::on_enter(Game& game)
{
}

void GameEndState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
}

void GameEndState::on_exit(Game& game)
{
}

std::string GameEndState::name()
{
	return "GameEndState";
}
