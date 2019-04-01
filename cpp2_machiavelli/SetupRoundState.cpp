#include "SetupRoundState.h"

void SetupRoundState::on_enter(Game& game)
{
	game.client_manager().notify_all_players("Successfully entered setup round!\r\n");
	game.game_manager().load_decks();
	std::cout << "Building cards: " << game.game_manager().building_card_deck_size() << "\n";
	std::cout << "Character cards: " << game.game_manager().character_card_deck_size() << "\n";
	this->add_starting_resources(game);
}

void SetupRoundState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	auto &client = client_info.get_socket();
	auto &player = client_info.get_player();
	client << player.get_name() << ", id: " << player.id() << ", you wrote: '" << command 
		<< "' in: " << name() << ", but I'll ignore that for now.\r\n" << "machiavelli> ";
}

void SetupRoundState::on_exit(Game& game)
{
}

std::string SetupRoundState::name()
{
	return "SetupRoundState";
}

void SetupRoundState::add_starting_resources(Game& game)
{
	auto& buildings_pile = game.game_manager().building_cards();
	auto& clients = game.client_manager().get_clients();
	Player& oldest = clients.at(0)->get_player();

	for (auto client : clients)
	{
		//init coins
		client->get_player().coins(2);
		//Draw building cards
		for(int i = 0; i < 4; i++)
		{
			client->get_player().add_building(buildings_pile.front());
			buildings_pile.pop_front();
		}
		//oldest player becomes king TODO: use kings_card instead of a bool?? In that case change that the filereader...
		if (client->get_player().age() > oldest.age())
		{
			oldest = client->get_player();
		}
	}
	oldest.king(true);
	game.client_manager().notify_all_players("Player: " + oldest.get_name() + " is the King! \r\n");	
}
