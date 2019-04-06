#include "AssassinState.h"
#include <algorithm>

void AssassinState::on_enter(Game& game)
{
	ClientInfo& client_info = game.client_manager().get_current_client();
	auto& socket = client_info.get_socket();

	socket.write("Pick a character to kill: \r\n"
		"[1] Nevermind, don't kill anyone.\r\n"
		"[2] Thief\r\n"
		"[3] Mage\r\n"
		"[4] King\r\n"
		"[5] Preacher\r\n"
		"[6] Merchant\r\n"
		"[7] Builder\r\n"
		"[8] Condottiere\r\n"
		"machiavelli> "
	);
}

void AssassinState::handle_input(Game& game, ClientInfo& client, const std::string& command)
{
	auto &socket = client.get_socket();
	auto &player = client.get_player();
	if(command == "1")
	{
		game.state_machine().change_state("GameRoundState");
	}

	//Kill the character
	else if(command == "2" || command == "3" || command == "4" || 
		command == "5" || command == "6" || command == "7" || command == "8")
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
				//Assassin uses his special
				if (c->get_player().id() == player.id() && char_card->id() == 1)
				{
					char_card->use_special();
				}

				//If a player has the chosen character, kill it.
				if(char_card->id() == char_id)
				{
					char_card->kill();
				}
			});
		});

		game.client_manager().notify_all_players("The Assassin killed the " + game.character_manager().get_name_by_id(char_id) + "\r\n");
		game.state_machine().change_state("GameRoundState");
	}
	else
	{
		socket << player.get_name() << ", id: " << player.id() << ", you wrote: '" << command
			<< "' but this Assassin can't handle that option, try again.\r\n" << "machiavelli> ";
	}
}

void AssassinState::on_exit(Game& game)
{
}

std::string AssassinState::name()
{
	return "AssassinState";
}
