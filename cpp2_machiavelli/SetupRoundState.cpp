#include "SetupRoundState.h"
#include <algorithm>
#include "King.h"

void SetupRoundState::on_enter(Game& game)
{
	//lock all clients and load the deque
	game.client_manager().lock_all_clients();
	game.game_manager().load_character_deque();
	game.client_manager().notify_all_players("Successfully entered setup round!\r\n");

	//get the king
	auto& client = *std::find_if(game.client_manager().get_clients().begin(), game.client_manager().get_clients().end(),
		[&](std::shared_ptr<ClientInfo>& client) {return client->get_player().king(); });
	std::unique_ptr<CharacterCard> king_card = std::make_unique<King>(4, "King");

	//add the king card
	client->get_player().add_character(std::move(king_card));

	//discard the top character card
	game.game_manager().get_top_character_card();

	//go to next player
	draw_characters(game.client_manager().get_next_client(client->get_player().id()).get_player().id(), game);
}

void SetupRoundState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	auto &client = client_info.get_socket();
	auto &player = client_info.get_player();

	try
	{
		//check on numbers and nullptr TODO: clean tis mess code up
		if(game.game_manager().get_character_card(std::stoi(command)) != nullptr)
		{
			game.client_manager().notify_player("Character card added! You now have the following character(s):  \r\n" + player.get_character_info(), player.id());
		} else
		{
			game.client_manager().notify_player("Your input is not valid, please try a valid number", player.id());
		}
		
	} catch(std::exception& ex)
	{
		game.client_manager().notify_player("Your input is not valid, please try a valid number", player.id());
	}
}

void SetupRoundState::on_exit(Game& game)
{
	//reset things
}

std::string SetupRoundState::name()
{
	return "SetupRoundState";
}

void SetupRoundState::draw_characters(int player_id, Game& game)
{
	auto& client = game.client_manager().get_client(player_id);

	//discard the top card of the deque
	game.game_manager().get_top_character_card();

	//notify the player that he needs to draw
	game.client_manager().notify_player("please choose one of the below character cards by typing the number of the card \r\n", player_id);
	game.client_manager().notify_player(game.game_manager().get_character_card_info(), player_id);
	
	//unlock the current player and start handling input
	game.client_manager().lock_client(player_id, false);
}



