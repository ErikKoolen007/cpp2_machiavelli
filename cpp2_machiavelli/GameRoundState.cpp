#include "GameRoundState.h"
#include <queue>

void GameRoundState::on_enter(Game& game)
{
	//Check whether the character is dead -> if so, skip to the next character
		//Check whether the character has been robbed -> if so, give all his money to the robbed_by player
		//check boolean to see if player has chosen coins or buildingcards already -> kan ik niet vinden?
			//give options accordingly
				//-choose coins or cards
				//-show round specific choices
					//Check whether character used his special ability
					//Show special ability option if not
	game.client_manager().notify_all_players("Successfully entered GameRoundState!");
	std::unordered_map<int, int>& routing_table = game.client_manager().get_round_routing_table();

	int character_id = game.game_manager().pop_character_order_queue();
	int player_id = routing_table.find(character_id)->second;

	auto current_player = game.client_manager().get_client(player_id).get_player();
	auto current_character = current_player.character_card(character_id);

	//check dead
	 if(!current_character->dead())
	 {
		 //check robbed
		if(current_character->robbed())
		{
			Player& robber = game.client_manager().get_client(current_character->robbed_by()).get_player();
			int amount = current_player.coins();
			current_player.coins(0);
			robber.add_coins(amount);
			game.client_manager().notify_player("Oi, you got robbed! " + 
				std::to_string(amount) + " (all) of your coins has been transferred to " + robber.get_name() + "\r\n", player_id);
		}

		 //show option buildings/coins
		game.client_manager().notify_player(
			current_player.get_character_info() + "\r\n\rn" 
			+ current_player.getInventoryInfo() + 
			"\r\n\r\n Do you want to have 'buildings' or 'coins'?\r\n", player_id);

		 //expect player input from here
		building_coin_input = true;
	 } else
	 {
		 game.client_manager().notify_player("Oi boi, you have been assassinated, you are skipping a turn now... \r\n", player_id);
	 }
}

void GameRoundState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	//handle input
		//If special ability is chosen: enter state of the character to handle it.

	//last player triggers setupround state/gameendstate -> check if game is won
	//lock the right player if the player ends his turn(lock logic is used to get currentclient in the character states)
}

void GameRoundState::on_exit(Game& game)
{
}

std::string GameRoundState::name()
{
	return "GameRoundState";
}
