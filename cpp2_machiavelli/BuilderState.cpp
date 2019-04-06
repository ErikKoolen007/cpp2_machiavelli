#include "BuilderState.h"

void BuilderState::on_enter(Game& game)
{
	ClientInfo& client_info = game.client_manager().get_current_client();
	auto& socket = client_info.get_socket();
	auto& player = client_info.get_player();

	socket.write("You got 2 cards from the deck!\r\n");
	//Draw building cards
	for (int i = 0; i < 2; i++)
	{
		client_info.get_player().add_building(game.game_manager().get_top_building_card());
	}
	game.character_manager().register_special_ability_used(player.id(), 7);

	game.state_machine().change_state("GameRoundState");
}

void BuilderState::handle_input(Game& game, ClientInfo& client, const std::string& command)
{
}

void BuilderState::on_exit(Game& game)
{
}

std::string BuilderState::name()
{
	return "BuilderState";
}
