#include "GameRoundState.h"

void GameRoundState::on_enter(Game& game)
{
	game.client_manager().notify_all_players("Successfully entered GameRoundState!");
}

void GameRoundState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
}

void GameRoundState::on_exit(Game& game)
{
}

std::string GameRoundState::name()
{
	return "GameRoundState";
}
