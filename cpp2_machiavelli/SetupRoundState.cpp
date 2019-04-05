#include "SetupRoundState.h"
#include <algorithm>

void SetupRoundState::on_enter(Game& game)
{
	auto& clients = game.client_manager().get_clients();
	bool first = true;

	game.client_manager().lock_all_clients();
	game.game_manager().load_character_deque();
	game.client_manager().notify_all_players("Successfully entered setup round!\r\n");

	//add starting sources for the round
	std::for_each(clients.begin(), clients.end(), [&](std::shared_ptr<ClientInfo>& client)
	{
		Player& curr_player = client->get_player();
		//unlock the current player
		game.client_manager().lock_client(curr_player.id(), false);

		if(curr_player.king())
		{
			//discard the top character card
			game.game_manager().get_top_character_card();

			if (first)
			{
				//choose a character card from the deque
				player_draws_character(curr_player.id(), game);
			} 
		} else
		{
			
		}
		first = false;
	});
	
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
}


