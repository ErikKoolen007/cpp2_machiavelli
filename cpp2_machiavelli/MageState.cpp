#include "MageState.h"

void MageState::on_enter(Game& game)
{
	ClientInfo& client_info = game.client_manager().get_current_client();
	auto& socket = client_info.get_socket();

	socket.write("Please choose an option:\r\n"
		"[1] Nevermind, don't do anything"
		"[2] Trade all cards with the other player"
		"[3] Remove x amount of cards and get the same amount of new ones"
		"machiavelli> "
	);
}

void MageState::handle_input(Game& game, ClientInfo& client, const std::string& command)
{
	auto &socket = client.get_socket();
	auto &player = client.get_player();

	if(command == "1" && !sub_menu_)
	{
		game.state_machine().change_state("GameRoundState");
	}
	else if(command == "2" && !sub_menu_)
	{
		game.character_manager().register_special_ability_used(player.id(), 3);

		//Swap hand with other player
		ClientInfo& other_client = game.client_manager().get_next_client(player.id());
		player.building_cards().swap(other_client.get_player().building_cards());
		game.client_manager().notify_all_players("Your building hand has been swapped with the other player by the Mage!\r\n");

		game.state_machine().change_state("GameRoundState");
	}
	else if(command == "3" && !sub_menu_)
	{
		sub_menu_ = true;
		game.character_manager().register_special_ability_used(player.id(), 3);
		socket.write("Choose an amount of cards between 1 and " + std::to_string(player.building_cards().size()) + "\r\nmachiavelli> ");
	}
	else if(sub_menu_ && isdigit(command[0]))
	{
		const int option_amount = std::stoi(command);
		if(option_amount > 0 && option_amount <= static_cast<int>(player.building_cards().size()))
		{
			//remove "option_amount" of hand building cards
			player.remove_hand_buildings(option_amount);

			//Draw building cards to the option_amount
			for (int i = 0; i < option_amount; i++)
			{
				player.add_building(game.game_manager().get_top_building_card());
			}
			socket.write("You removed " + std::to_string(option_amount) + "cards from your hand and got the same amount from the deck.\r\n");

			game.state_machine().change_state("GameRoundState");
		}
		else
		{
			socket << player.get_name() << ", id: " << player.id() << ", you wrote: '" << command
				<< "' but that option is not available, try again.\r\n" << "machiavelli> ";
		}
	}
	else
	{
		socket << player.get_name() << ", id: " << player.id() << ", you wrote: '" << command
			<< "' but this Mage can't handle that option, try again.\r\n" << "machiavelli> ";
	}
}

void MageState::on_exit(Game& game)
{
	sub_menu_ = false;
}

std::string MageState::name()
{
	return "MageState";
}
