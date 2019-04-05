#include "SetupRoundState.h"
#include <algorithm>

void SetupRoundState::on_enter(Game& game)
{
	game.client_manager().lock_all_clients();
	game.game_manager().load_character_deque();
	game.client_manager().notify_all_players("Successfully entered setup round!\r\n");
	this->add_starting_resources(game);
	
}

void SetupRoundState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	auto &client = client_info.get_socket();
	auto &player = client_info.get_player();

	// client << player.get_name() << ", id: " << player.id() << ", you wrote: '" << command 
	// 	<< "' in: " << name() << ", but I'll ignore that for now.\r\n" << "machiavelli> ";
}

void SetupRoundState::on_exit(Game& game)
{

}

std::string SetupRoundState::name()
{
	return "SetupRoundState";
}

void SetupRoundState::player_draws_character(int player_id, Game& game)
{
	auto& client = game.client_manager().get_client(player_id);
	auto& character_deque = game.game_manager().character_cards();

	//notify the player that he needs to draw
	game.client_manager().notify_player(game.game_manager().get_character_card_info(), player_id);
	game.client_manager().notify_player("please choose one of the above charactercards by typing the number", player_id);

	//unlock the current player and start handling input
	game.client_manager().lock_client(player_id, false);
}

void SetupRoundState::add_starting_resources(Game& game)
{
	auto& clients = game.client_manager().get_clients();
	bool first = true;

	//add starting resources for the round
	std::for_each(clients.begin(), clients.end(), [&](std::shared_ptr<ClientInfo>& client)
	{
		Player& curr_player = client->get_player();

		if (curr_player.king())
		{
			//discard the top character card
			game.game_manager().get_top_character_card();

			if (!first)
			{
				//choose a character card from the deque
				player_draws_character(curr_player.id(), game);
			}
		}
		else
		{

		}
		first = false;
	});
}


