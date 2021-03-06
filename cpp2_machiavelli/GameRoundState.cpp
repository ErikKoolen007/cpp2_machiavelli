#include "GameRoundState.h"
#include <queue>

void GameRoundState::on_enter(Game& game)
{
	game.client_manager().notify_all_players("Successfully entered GameRoundState!\r\n");
	std::unordered_map<int, int>& routing_table = game.client_manager().get_round_routing_table();
	bool done = false;

	character_id_ = game.game_manager().get_character_order_queue().front();

	if (routing_table.count(character_id_))
	{
		player_id_ = routing_table.find(character_id_)->second;

		//added from here
		Player& current_player = game.client_manager().get_client(player_id_).get_player();
		std::shared_ptr<CharacterCard>& current_character = current_player.character_card(character_id_);

		//lock all the clients (it is possible that one of them is not locked at this stage
		game.client_manager().lock_all_clients();
		//check dead
		if (!current_character->dead())
		{
			//check robbed
			if (current_character->robbed())
			{
				Player& robber = game.client_manager().get_client(current_character->robbed_by()).get_player();
				const int amount = current_player.coins();
				current_player.coins(0);
				robber.add_coins(amount);
				game.client_manager().notify_player("Oi, you got robbed! " +
					std::to_string(amount) + " (all) of your coins has been transferred to " + robber.get_name() + "\r\n", player_id_);
			}

			//check merchant
			if (current_character->name() == "Koopman")
			{
				current_player.add_coins(1);
			}

			//give the player his information
			game.client_manager().notify_player(
				current_player.get_character_info() +
				current_player.getInventoryInfo() + "\r\n" +
				current_player.get_played_buildings_info() + "\r\n\r\n" +
				"This turn you play for the " + current_character->name() + "\r\n\r\n" +
				generate_options_msg(current_character), player_id_);

			//expect player input from here
			game.client_manager().lock_client(player_id_, false);
		}
		else
		{
			if (current_character->name() == "Koning")
			{
				king_killed_ = true;
			}
			game.client_manager().notify_player("Oi boi, you have been assassinated, you are skipping a turn now... \r\n", player_id_);
			end_turn(game);
		}
	}
	else
	{
		game.client_manager().notify_all_players("The King called for the " + game.character_manager().get_name_by_id(character_id_)
			+ " but none answered.\r\n");

		end_turn(game);
	}
}

void GameRoundState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	Player& current_player = game.client_manager().get_client(player_id_).get_player();
	std::shared_ptr<CharacterCard>& current_character = current_player.character_card(character_id_);


	if (command == "build" && !building_)
	{
		building_ = true;
		int i = 1;
		std::string option_msg = "";
		std::for_each(current_player.building_cards().begin(), current_player.building_cards().end(), [&](BuildingCard& option)
		{
			option_map_.insert({i, option});
			option_msg = option_msg + "[" + std::to_string(i) + "] " + option.to_string() + "\r\n";
			i++;
		});

		game.client_manager().notify_player(std::string("Which building do you want to build? Please type the number of the card \r\n") +
			option_msg, player_id_);
	}

	else if (command == "special power" && !building_)
	{
		switch (character_id_) {
		case 1:
			game.client_manager().trigger_next_state("AssassinState");
			break;
		case 2:
			game.client_manager().trigger_next_state("ThiefState");
			break;
		case 3:
			game.client_manager().trigger_next_state("MageState");
			break;
		case 4:
			game.client_manager().trigger_next_state("KingState");
			break;
		case 5:
			game.client_manager().trigger_next_state("PreacherState");
			break;
		case 6:
			game.client_manager().trigger_next_state("MerchantState");
			break;
		case 7:
			game.client_manager().trigger_next_state("BuilderState");
			break;
		case 8:
			game.client_manager().trigger_next_state("CondottiereState");
			break;
		default:;
		}
	}
	else if (command == "building card" && !building_)
	{
		building_coins_used_ = true;
		current_player.add_building(game.game_manager().get_top_building_card());
		game.client_manager().notify_player("\r\n a building card has been added to your inventory, you now have the following building cards in your hand:\r\n " +
			current_player.get_building_info() + "\r\n\r\n" + generate_options_msg(current_character), player_id_);
	}

	else if (command == "coins" && !building_)
	{
		building_coins_used_ = true;
		current_player.add_coins(2);
		game.client_manager().notify_player("\r\n2 coins have been added, You now have " + 
			std::to_string(current_player.coins()) + " coins \r\n\r\n" + generate_options_msg(current_character), player_id_);
	}

	else if (command == "help" && !building_)
	{
		game.client_manager().notify_player(generate_help_msg(), player_id_);
	}

	else if (command == "back" && building_)
	{
		building_ = false;
		game.client_manager().notify_player(generate_options_msg(current_character), player_id_);
	}

	else if (command == "end" && !building_)
	{
		end_turn(game);
	} 
	
	else if(building_)
	{
		try
		{
			if (option_map_.find(std::stoi(command)) == option_map_.end())
			{
				throw std::exception();
			}
			BuildingCard selected_card = option_map_.find(std::stoi(command))->second;
			if (current_player.coins() - selected_card.points() < 0)
			{
				game.client_manager().notify_player("Sorry, you cannot build this building, the cost of this building is: " +
					std::to_string(selected_card.points()) + " and you have only " +
					std::to_string(current_player.coins()) + " coins. Go back by typing 'back' \r\n", player_id_);
			}
			else
			{
				current_player.transfer_buildings_to_table(selected_card.name());
				current_player.add_coins(selected_card.points() *-1);
				game.client_manager().notify_player("Building " + selected_card.name() + "built! \r\n" +
					current_player.getInventoryInfo() + current_player.get_played_buildings_info(), player_id_);
				building_ = false;
				buildings_built_++;
				game.client_manager().notify_player(generate_options_msg(current_character), player_id_);
			}
		}
		catch (std::exception& ex)
		{
			game.client_manager().notify_player("\r\nYour input is not valid, please try a valid number.\r\n", player_id_);
		}
	}
	else
	{
		game.client_manager().notify_player("unrecognized command, please try again", player_id_);
	}
}

void GameRoundState::on_exit(Game& game)
{
}

std::string GameRoundState::name()
{
	return "GameRoundState";
}

std::string GameRoundState::generate_options_msg(std::shared_ptr<CharacterCard>& current_character) const
{
	std::string console_msg = "";

	if(!building_coins_used_)
	{
		console_msg = console_msg + "You can choose if you want 'coins' or a 'building card'\r\n";
	}

	if((current_character->name() != "Bouwmeester" && buildings_built_ < 1) || 
		(current_character->name() == "Bouwmeester" && buildings_built_ < 3))
	{
		console_msg = console_msg + "You can choose if you want 'build' a building\r\n";
	}

	if(!current_character->special_used())
	{
		console_msg = console_msg + "You can choose if you want to use your 'special power' \r\n";
	}

	console_msg = console_msg + "You can end your turn by typing 'end'\r\n" +
						"If you need help type 'help'";
	return console_msg;
}

std::string GameRoundState::generate_help_msg()
{
	return std::string("1. Moordenaar: kills another character \r\n") + 
		std::string("2. Dief: robs another character's coins \r\n") + 
		std::string("3. Magi�r: can swap building cards \r\n") +
		std::string("4. Koning: is the start player of the turn, gains from monuments \r\n") +
		std::string("5. Prediker: is immune for actions of the Condotierre, gains from religious buildings \r\n") +
		std::string("6. Koopman: gains an extra coin, gains additionally from commercial buildings\r\n") + 
		std::string("7. Bouwmeester: can draw 2 extra building cards, can build 3 buildings in a turn\r\n") + 
		std::string("8. Condottierre: can destroy a building, gains from military buildings \r\n");
}

void GameRoundState::handle_build_building()
{

}

void GameRoundState::end_turn(Game& game)
{
	//reset booleans and int for next round
	buildings_built_ = 0;
	building_coins_used_ = false;
	building_ = false;
	option_map_.clear();
	game.client_manager().clear_round_routing_table();

	//Check if there is a next character
	if (game.game_manager().get_character_order_queue_size() > 1)
	{
		game.game_manager().pop_character_order_queue();
		game.client_manager().trigger_next_state("GameRoundState");
	}
	else
	{
		//check endgame
		if (game.client_manager().check_if_eight_buildings())
		{
			game.client_manager().trigger_next_state("GameEndState");
		}
		else
		{
			//choose next king
			if (!king_killed_)
			{
				auto& current_king = game.client_manager().get_king();
				current_king.get_player().king(false);
				game.client_manager().get_next_client(player_id_).get_player().king(true);
			}
			king_killed_ = false;
			game.client_manager().trigger_next_state("SetupRoundState");
		}
	}
}
