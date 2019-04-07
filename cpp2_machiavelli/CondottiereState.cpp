#include "CondottiereState.h"
#include <algorithm>

void CondottiereState::on_enter(Game& game)
{
	ClientInfo& client_info = game.client_manager().get_current_client();
	auto& socket = client_info.get_socket();
	auto& player = client_info.get_player();

	//Get gold from each red building
	int red_buildings = 0;
	std::for_each(player.building_cards_on_table().begin(), player.building_cards_on_table().end(), [&](BuildingCard& building_card)
	{
		if (building_card.color() == "rood")
		{
			red_buildings++;
		}
	});
	player.add_coins(red_buildings);
	game.character_manager().register_special_ability_used(player.id(), 8);

	socket.write("You got " + std::to_string(red_buildings) + " gold from your red buildings!\r\n");
	ClientInfo& other_client = game.client_manager().get_next_client(player.id());

	//If the other client has no buildings, 8 or more buildings or has the preacher card, no buildings can be demolished
	const int other_table_size = other_client.get_player().building_cards().size();
	if(other_table_size == 0 || other_table_size > 7 || other_client.get_player().has_character_card(5))
	{
		socket.write("Sorry, there are no buildings available to demolish.");
		game.state_machine().change_state("GameRoundState");
	}
	//Choose the building to destroy
	else
	{
		auto& other_client_table_buildings = other_client.get_player().building_cards_on_table();
		building_option_count_ = 0;
		option_map_.clear();
		int index = 0;
		std::for_each(other_client_table_buildings.begin(), other_client_table_buildings.end(), [&](BuildingCard& building_card)
		{
			//If the player has enough coins to demolish the building, add it to the options
			if(building_card.points() - 1 <= player.coins())
			{
				building_option_count_++;
				socket.write("[" + std::to_string(building_option_count_) + "] " + building_card.to_string() + "\r\n");
				option_map_.insert(std::make_pair(building_option_count_, index));
			}
			index++;
		});

		if(building_option_count_ == 0)
		{
			socket.write("You don't have enough money to destroy any building\r\n");
			game.state_machine().change_state("GameRoundState");
		}
		else
		{
			socket.write("machiavelli> ");
		}
	}
}

void CondottiereState::handle_input(Game& game, ClientInfo& client, const std::string& command)
{
	auto &socket = client.get_socket();
	auto &player = client.get_player();

	if(command == "1" || command == "2" || command == "3" || command == "4" || command == "5" || command == "6" || command == "7")
	{
		const int option_id = std::stoi(command);
		if(option_id <= building_option_count_)
		{
			ClientInfo& other_client = game.client_manager().get_next_client(player.id());
			const std::string destroyed_building = other_client.get_player().building_cards_on_table()[option_map_[option_id]].to_string();

			game.client_manager().notify_all_players("The Condottiere destroyed the " + destroyed_building + "from: " + 
				other_client.get_player().get_name() + "!\r\n");
			other_client.get_player().destroy_building(option_map_[option_id]);
			game.state_machine().change_state("GameRoundState");
		}
		else
		{
			socket << player.get_name() << ", id: " << player.id() << ", you wrote: '" << command
				<< "' but this option is not available, try again.\r\n" << "machiavelli> ";
		}
	}
	else
	{
		socket << player.get_name() << ", id: " << player.id() << ", you wrote: '" << command
			<< "' but this Condottiere can't handle that option, try again.\r\n" << "machiavelli> ";
	}
}

void CondottiereState::on_exit(Game& game)
{
}

std::string CondottiereState::name()
{
	return "CondottiereState";
}
