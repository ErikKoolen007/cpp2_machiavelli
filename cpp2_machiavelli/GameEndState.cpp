#include "GameEndState.h"
#include <algorithm>

void GameEndState::on_enter(Game& game)
{
	ClientInfo& client_info = game.client_manager().get_current_client();
	auto& player = client_info.get_player();
	ClientInfo& other_client = game.client_manager().get_next_client(player.id());
	auto& other_player = other_client.get_player();

	game.client_manager().notify_all_players("The game has ended! Calculating player score...\r\n");

	std::for_each(game.client_manager().get_clients().begin(), game.client_manager().get_clients().end(), [&](std::shared_ptr<ClientInfo>& c)
	{
		auto& p = c->get_player();
		bool red_building, blue_building, yellow_building, green_building, lila_building = false;

		//Give points for each building in the city
		std::for_each(p.building_cards_on_table().begin(), p.building_cards_on_table().end(), [&](BuildingCard& building_card)
		{
			p.add_points(building_card.points());
			p.add_building_card_points(building_card.points());

			if (building_card.color() == "rood")
				red_building = true;
			if (building_card.color() == "blauw")
				blue_building = true;
			if (building_card.color() == "geel")
				yellow_building = true;
			if (building_card.color() == "groen")
				green_building = true;
			if (building_card.color() == "lila")
				lila_building = true;
		});

		//Give 4 score for player with first full city
		if(p.first_full_city())
		{
			p.add_points(4);
		}
		//Give 2 score for each player with 8 buildings but not the first_full_city player
		else if(p.building_cards_on_table().size() > 7)
		{
			p.add_points(2);
		}
		//Give 3 points if player has all 5 different colors
		if(red_building && blue_building && yellow_building && green_building && lila_building)
		{
			p.add_points(3);
		}
	});

	if(player.points() > other_player.points())
	{
		game.client_manager().notify_all_players(player.get_name() + " won with " 
			+ std::to_string(player.points()) + " points!\r\n");
	}
	else if(player.points() < other_player.points())
	{
		game.client_manager().notify_all_players(other_player.get_name() + " won with " 
			+ std::to_string(other_player.points()) + " points!\r\n");
	}
	else
	{
		if(player.building_card_points() > other_player.building_card_points())
		{
			game.client_manager().notify_all_players(player.get_name() + " won with " + 
				std::to_string(player.points()) + " points, building points being the tie breaker!\r\n");
		}
		else if(player.building_card_points() < other_player.building_card_points())
		{
			game.client_manager().notify_all_players(other_player.get_name() + " won with " 
				+ std::to_string(other_player.points()) + " points, building points being the tie breaker!\r\n");
		}
		else
		{
			game.client_manager().notify_all_players("It's a tie with " + std::to_string(player.points()) 
				+ " points!!! Congratulations to you both!\r\n");
		}
	}

	game.client_manager().notify_all_players("The game will now return to the starting state. "
		"Please type 'quit' if you want to leave or 'quit_server to terminate the server'");

	game.state_machine().change_state("PreGameState");
}

void GameEndState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
}

void GameEndState::on_exit(Game& game)
{
	game.client_manager().reset_players();
}

std::string GameEndState::name()
{
	return "GameEndState";
}
