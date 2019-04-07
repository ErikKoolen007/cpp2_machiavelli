#include "GameRoundState.h"
#include <queue>

void GameRoundState::on_enter(Game& game)
{
	game.client_manager().notify_all_players("Successfully entered GameRoundState!\r\n");
	std::unordered_map<int, int>& routing_table = game.client_manager().get_round_routing_table();

	int character_id = game.game_manager().pop_character_order_queue();
	current_player_id_ = routing_table.find(character_id)->second;
	Player& current_player = game.client_manager().get_client(current_player_id_).get_player();
	std::shared_ptr<CharacterCard>& current_character = current_player.character_card(character_id);

	//lock all the clients (it is possible that one of them is not locked at this stage
	game.client_manager().lock_all_clients();
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
				std::to_string(amount) + " (all) of your coins has been transferred to " + robber.get_name() + "\r\n", current_player_id_);
		}
		 //give the player his information
		game.client_manager().notify_player(
			current_player.get_character_info() +
			current_player.getInventoryInfo() + "\r\n" +
			current_player.get_played_buildings_info() + "\r\n\r\n" +
			"This turn you play for the " + current_character->name() +  "\r\n\r\n" +
			generate_options_msg(current_character), current_player_id_);

		 //expect player input from here
		game.client_manager().lock_client(current_player_id_, false);
	 } else
	 {
		 game.client_manager().notify_player("Oi boi, you have been assassinated, you are skipping a turn now... \r\n", current_player_id_);
	 }
}

void GameRoundState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	//excepton handle this method

	if(command == "build")
	{
		//game.client_manager().
	}

	if(command == "special power")
	{
		
	}

	if(command == "building card")
	{
		
	}

	if(command == "coins")
	{
		
	}

	if (command == "help")
	{
		game.client_manager().notify_player(generate_help_msg(), current_player_id_);
	}

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

	if(!building_coins_used_)
	{
		console_msg = console_msg + "Choose if you want 'coins' or a 'building card'\r\n";
	}

	if((current_character->name() != "Bouwmeester" && buildings_built_ < 1) || 
		(current_character->name() == "Bouwmeester" && buildings_built_ < 3))
	{
		console_msg = console_msg + "Or choose if you want 'build' a building\r\n";
	}

	if(!current_character->special_used())
	{
		console_msg = console_msg + "Or choose if you want to use your 'special power' \r\n";
	}

	console_msg = console_msg + "Or end your turn by typing 'end'\r\n" +
						"If you need help type 'help'";
	return console_msg;
}

std::string GameRoundState::generate_help_msg()
{
	return std::string("1. Moordenaar: kills another character \r\n") + 
		std::string("2. Dief: robs another character's coins \r\n") + 
		std::string("3. Magiër: can swap building cards \r\n") +
		std::string("4. Koning: is the start player of the turn, gains from monuments \r\n") +
		std::string("5. Prediker: is immune for actions of the Condotierre, gains from religious buildings \r\n") +
		std::string("6. Koopman: gains an extra coin, gains additionally from commercial buildings\r\n") + 
		std::string("7. Bouwmeester: can draw 2 extra building cards, can build 3 buildings in a turn\r\n") + 
		std::string("8. Condottierre: can destroy a building, gains from military buildings \r\n");
}
