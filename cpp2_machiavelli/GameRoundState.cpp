#include "GameRoundState.h"

void GameRoundState::on_enter(Game& game)
{
	game.client_manager().notify_all_players("Successfully entered GameRoundState!");
	//choose the right player who has to play based on his charactres (construct hashmap with player id as key and list of charactercards?)
		//TODO whatever check this is gonna be. do it in a manager for persistence reasons.

	//Check whether the character is dead -> if so, skip to the next character
	//Check whether the character has been robbed -> if so, give all his money to the robbed_by player
	//check boolean to see if player has chosen coins or buildingcards already
		//give options accordingly
			//-choose coins or cards
			//-show round specific choices
				//Check whether character used his special ability
				//Show special ability option if not

	//add resources at the start of the turn if needed
}

void GameRoundState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	//unlock the right player
	//handle input
		//If special ability is chosen: enter state of the character to handle it.

	//last player triggers setupround state/gameendstate -> check if game is won
	//lock the right player if the player ends his turn(lock logic is used to get currentclient in the character states)
}

void GameRoundState::on_exit(Game& game)
{
	//clear the characters of all players TODO: do this on start of setupround
}

std::string GameRoundState::name()
{
	return "GameRoundState";
}
