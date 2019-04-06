#include "MerchantState.h"
#include <algorithm>

void MerchantState::on_enter(Game& game)
{
	ClientInfo& client_info = game.client_manager().get_current_client();
	auto& socket = client_info.get_socket();
	auto& player = client_info.get_player();

	//Get gold from each green building
	int green_buildings = 0;
	std::for_each(player.building_cards_on_table().begin(), player.building_cards_on_table().end(), [&](BuildingCard& building_card)
	{
		if(building_card.color() == "groen")
		{
			green_buildings++;
		}
	});
	player.add_coins(green_buildings);
	game.character_manager().register_special_ability_used(player.id(), 6);

	socket.write("You got " + std::to_string(green_buildings) + " gold from your green buildings!");
	game.state_machine().change_state("GameRoundState");
}

void MerchantState::handle_input(Game& game, ClientInfo& client, const std::string& command)
{
}

void MerchantState::on_exit(Game& game)
{
}

std::string MerchantState::name()
{
	return "MerchantState";
}
