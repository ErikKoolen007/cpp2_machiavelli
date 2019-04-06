#include "PreacherState.h"
#include <algorithm>

void PreacherState::on_enter(Game& game)
{
	ClientInfo& client_info = game.client_manager().get_current_client();
	auto& socket = client_info.get_socket();
	auto& player = client_info.get_player();

	//Get gold from each blue building
	int blue_buildings = 0;
	std::for_each(player.building_cards_on_table().begin(), player.building_cards_on_table().end(), [&](BuildingCard& building_card)
	{
		if (building_card.color() == "blauw")
		{
			blue_buildings++;
		}
	});
	player.add_coins(blue_buildings);
	game.character_manager().register_special_ability_used(player.id(), 5);

	socket.write("You got " + std::to_string(blue_buildings) + " gold from your blue buildings!");
	game.state_machine().change_state("GameRoundState");
}

void PreacherState::handle_input(Game& game, ClientInfo& client, const std::string& command)
{
}

void PreacherState::on_exit(Game& game)
{
}

std::string PreacherState::name()
{
	return "PreacherState";
}
