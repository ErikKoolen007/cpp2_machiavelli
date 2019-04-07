#include "PreGameState.h"

void PreGameState::on_enter(Game& game)
{
	game.client_manager().notify_all_players("Successfully entered pre game!\r\n");
	if (game.client_manager().get_client_count() > 1)
	{
		//Start game with setup round
		game.state_machine().change_state("SetupRoundState");
	}
	else
	{
		game.client_manager().notify_all_players("The game will begin when another player joins.\r\n");
	}
}

void PreGameState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	auto &client = client_info.get_socket();
	auto &player = client_info.get_player();
	client << player.get_name() << ", id: " << player.id() << ", you wrote: '" << command
		<< "' in: " << name() << ", but I'll ignore that for now.\r\n" << "machiavelli> ";
}

void PreGameState::on_exit(Game& game)
{
	this->add_starting_resources(game);
}

std::string PreGameState::name()
{
	return "PreGameState";
}

void PreGameState::add_starting_resources(Game& game)
{
	game.game_manager().load_building_deque();
	auto& clients = game.client_manager().get_clients();
	int oldest_id = clients.at(0)->get_player().id();

	for (auto& client : clients)
	{
		//init coins
		client->get_player().coins(2);
		//Draw building cards
		for (int i = 0; i < 4; i++)
		{
			client->get_player().add_building(game.game_manager().get_top_building_card());
		}

		//oldest player becomes king
		if (client->get_player().age() > game.client_manager().get_client(oldest_id).get_player().age())
		{
			oldest_id = client->get_player().id();
		}
		//send notification to each player
		game.client_manager().notify_player(client->get_player().getInventoryInfo(), client->get_player().id());
		game.client_manager().notify_player(client->get_player().get_character_info(), client->get_player().id());

	}
	Player& oldest_player = game.client_manager().get_client(oldest_id).get_player();
	oldest_player.king(true);
	game.client_manager().notify_all_players("Player: " + oldest_player.get_name() + " is the King! \r\n\r\n");
}