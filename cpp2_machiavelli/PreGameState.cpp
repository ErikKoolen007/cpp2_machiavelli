#include "PreGameState.h"

void PreGameState::on_enter(Game& game)
{
	game.client_manager().notify_all_players("Successfully entered pre game!\r\n");
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
	game.game_manager().load_character_deque();
}

std::string PreGameState::name()
{
	return "PreGameState";
}

void PreGameState::add_starting_resources(Game& game)
{
	game.game_manager().load_building_deque();
	auto& clients = game.client_manager().get_clients();
	Player& oldest = clients.at(0)->get_player();

	for (auto client : clients)
	{
		//init coins
		client->get_player().coins(2);
		//Draw building cards
		for (int i = 0; i < 4; i++)
		{
			client->get_player().add_building(game.game_manager().get_top_card());
		}

		//oldest player becomes king
		if (client->get_player().age() > oldest.age())
		{
			oldest = client->get_player();
		}
		//send notification to each player
		game.client_manager().notify_player(client->get_player().getInventoryInfo(), client->get_player().id());
		game.client_manager().notify_player(client->get_player().getCharacterInfo(), client->get_player().id());

	}
	oldest.king(true);
	game.client_manager().notify_all_players("Player: " + oldest.get_name() + " is the King! \r\n");
}