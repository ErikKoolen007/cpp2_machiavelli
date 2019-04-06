#include "GameRoundState.h"

void GameRoundState::on_enter(Game& game)
{
	game.client_manager().notify_all_players("Succesfully entered GameRoundState!");
	//choose the right player who has to play based on his charactres (construct hashmap with player id as key and list of charactercards?)
	//add resources at the start of the turn if needed
}

void GameRoundState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	//unlock the right player
	//make character specific choices and act on that

	//last player triggers setupround state/gameendstate -> check if game is won
	//lock the right player
}

void GameRoundState::on_exit(Game& game)
{
	//clear the characters of all players
}

std::string GameRoundState::name()
{
	return "GameRoundState";
}
