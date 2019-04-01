#include "SetupRoundState.h"

void SetupRoundState::on_enter(Game& game)
{
	game.client_manager().notify_all_players("Successfully entered setup round!\r\n");
	game.game_manager().load_decks();
	std::cout << "Building cards: " << game.game_manager().building_card_deck_size() << "\n";
	std::cout << "Character cards: " << game.game_manager().character_card_deck_size() << "\n";

	//oldest player becomes king
	Player& oldest = game.client_manager().get_clients().at(0)->get_player();
	for(auto client : game.client_manager().get_clients())
	{
		if(client->get_player().age() > oldest.age())
		{
			oldest = client->get_player();
		}
	}
	oldest.king(true);
	game.client_manager().notify_all_players("Player: " + oldest.get_name() + " is the King! \r\n");
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
