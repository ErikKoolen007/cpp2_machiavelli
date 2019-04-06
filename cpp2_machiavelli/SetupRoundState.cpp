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
	auto& king = game.client_manager().get_king();
	std::unique_ptr<CharacterCard> king_card = std::make_unique<King>(4, "King");

	//add the king card
	king.get_player().add_character(std::move(king_card));

	//discard the top character card
	game.game_manager().get_top_character_card();

	//go to next player
	draw_characters(game.client_manager().get_next_client(king.get_player().id()).get_player().id(), game);
}

void SetupRoundState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	auto &player = client_info.get_player();

	try
	{
		auto selected_card = game.game_manager().get_character_card(std::stoi(command));
		if (selected_card != nullptr)
		{
			player.add_character(std::move(selected_card));
			game.client_manager().notify_player("\r\nCharacter card added! You now have the following character(s):  \r\n" + player.get_character_info(), player.id());
			game.client_manager().lock_client(player.id(), true);
			draw_characters(game.client_manager().get_next_client(player.id()).get_player().id(), game);
		} else
		{
			game.client_manager().notify_player("\r\nThe '" + command + "' input did not return a card, please enter a valid number.\r\n", player.id());
		}
		
	} catch(std::exception& ex)
	{
		game.client_manager().notify_player("\r\nYour input is not valid, please try a valid number.\r\n", player.id());
	}
}

void SetupRoundState::on_exit(Game& game)
{
}

std::string SetupRoundState::name()
{
	return "SetupRoundState";
}

void SetupRoundState::draw_characters(int player_id, Game& game)
{
	if(game.game_manager().character_card_deck_size() > 1)
	{
		auto& client = game.client_manager().get_client(player_id);

		//discard the top card of the deque
		game.game_manager().get_top_character_card();

		//notify the player that he needs to draw
		game.client_manager().notify_player("please choose one of the below character cards by typing the number of the card \r\n", player_id);
		game.client_manager().notify_player(game.game_manager().get_character_card_info(), player_id);

		//unlock the current player and start handling input
		game.client_manager().lock_client(player_id, false);
	} else
	{
		//character deque is empty now go to GameRoundState ->
		game.client_manager().trigger_next_state("GameRoundState");
		
		//TODO remove test code when done
		//game.client_manager().lock_client(player_id, false);
		//game.client_manager().trigger_next_state("BuilderState");
		
	}
}



