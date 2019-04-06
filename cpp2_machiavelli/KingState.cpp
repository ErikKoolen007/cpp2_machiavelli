#include "KingState.h"
#include <algorithm>

void KingState::on_enter(Game& game)
{
	ClientInfo& client_info = game.client_manager().get_current_client();
	auto& socket = client_info.get_socket();
	auto& player = client_info.get_player();

	//Get gold from each yellow building
	int yellow_buildings = 0;
	std::for_each(player.building_cards_on_table().begin(), player.building_cards_on_table().end(), [&](BuildingCard& building_card)
	{
		if (building_card.color() == "geel")
		{
			yellow_buildings++;
		}
	});
	player.add_coins(yellow_buildings);
	game.character_manager().register_special_ability_used(player.id(), 4);

	socket.write("You got " + std::to_string(yellow_buildings) + " gold from your yellow buildings!");
	game.state_machine().change_state("GameRoundState");
}

void KingState::handle_input(Game& game, ClientInfo& client, const std::string& command)
{
}

void KingState::on_exit(Game& game)
{
}

std::string KingState::name()
{
	return "KingState";
}
