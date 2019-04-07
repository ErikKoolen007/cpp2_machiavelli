#include "GameRoundState.h"
#include <queue>

void GameRoundState::on_enter(Game& game)
{
	game.client_manager().notify_all_players("Successfully entered GameRoundState!");
	std::unordered_map<int, int>& routing_table = game.client_manager().get_round_routing_table();

	int character_id = game.game_manager().pop_character_order_queue();
	int player_id = routing_table.find(character_id)->second;
	Player& current_player = game.client_manager().get_client(player_id).get_player();
	std::shared_ptr<CharacterCard>& current_character = current_player.character_card(character_id);

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
		 //give the player his information
		game.client_manager().notify_player(
			current_player.get_character_info() +
			current_player.getInventoryInfo() + "\r\n" +
			generate_options_msg(current_character), player_id);

		 //expect player input from here
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

	if (command == "end")
	{
		
	}
}

void GameRoundState::on_exit(Game& game)
{
}

std::string GameRoundState::name()
{
	return "GameRoundState";
}

std::string GameRoundState::generate_options_msg(std::shared_ptr<CharacterCard>& current_character)
{
	std::string console_msg = "";

	if(!building_coins_used)
	{
		console_msg = console_msg + "Choose if you want 'coins' or a 'building card'\r\n";
	}

	if((current_character->name() != "Bouwmeester" && buildings_built < 1) || 
		(current_character->name() == "Bouwmeester" && buildings_built < 3))
	{
		console_msg = console_msg + "Or choose if you want 'build' a building\r\n";
	}

	if(!current_character->special_used())
	{
		console_msg = console_msg + "Or choose if you want to use your 'special power' \r\n";
	}

	console_msg = console_msg + "Or end your turn by typing 'end turn'\r\n";
	return console_msg;
}
