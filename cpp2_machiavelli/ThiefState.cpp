#include "ThiefState.h"
#include <algorithm>

void ThiefState::on_enter(Game& game)
{
	ClientInfo& client_info = game.client_manager().get_current_client();
	Socket& socket = client_info.get_socket();

	print_target_options(socket);
}

void ThiefState::handle_input(Game& game, ClientInfo& client, const std::string& command)
{
	auto &socket = client.get_socket();
	auto &player = client.get_player();
	stole_from_dead_character_ = false;

	if (command == "1")
	{
		game.state_machine().change_state("GameRoundState");
	}
	else if (command == "3" || command == "4" || command == "5" || command == "6" || command == "7" || command == "8")
	{
		int char_id = std::stoi(command);

		//For each player
		std::for_each(game.client_manager().get_clients().begin(), game.client_manager().get_clients().end(),
			[&](std::shared_ptr<ClientInfo>& c)
		{
			//Check each card
			std::for_each(c->get_player().character_cards().begin(), c->get_player().character_cards().end(),
				[&](std::shared_ptr<CharacterCard>& char_card)
			{
				//Thief uses his special
				if (c->get_player().id() == player.id() && char_card->id() == 2)
				{
					char_card->use_special();
				}

				//If a player has the chosen character, steal from it.
				if (char_card->id() == char_id)
				{
					if(char_card->dead())
					{
						socket.write("This character is dead, you can't steal from it. Please choose someone else");
						stole_from_dead_character_ = true;
						print_target_options(socket);
					}
					else 
					{
						char_card->rob(player.id());
					}
				}
			});
		});

		if (!stole_from_dead_character_) 
		{
			game.client_manager().notify_all_players("The Thief stole from someone!\r\n");
			game.state_machine().change_state("GameRoundState");
		}
	}
	else
	{
		socket << player.get_name() << ", id: " << player.id() << ", you wrote: '" << command
			<< "' but this Thief can't handle that option, try again.\r\n" << "machiavelli> ";
	}
}

void ThiefState::on_exit(Game& game)
{
}

std::string ThiefState::name()
{
	return "ThiefState";
}

void ThiefState::print_target_options(Socket& socket)
{
	socket.write("Pick a character to steal from: \r\n"
		"[1] Nevermind, don't rob anyone.\r\n"
		"[3] Mage\r\n"
		"[4] King\r\n"
		"[5] Preacher\r\n"
		"[6] Merchant\r\n"
		"[7] Builder\r\n"
		"[8] Condottiere\r\n"
		"machiavelli> "
	);
}
