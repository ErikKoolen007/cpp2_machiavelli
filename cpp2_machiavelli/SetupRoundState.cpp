#include "SetupRoundState.h"
#include <random>

//void SetupState::next()
//{
//}
//
//void SetupState::setup()
//{
//	this->building_cards_ = file_reader_->load_building_cards();
//	this->character_cards_ = file_reader_->load_character_cards();
//	//generate seed and shuffle buildingcards
//	std::random_device rd;
//	std::mt19937 g(rd());
//	std::shuffle(building_cards_->begin(), building_cards_->end(), g);
//}

void SetupRoundState::on_enter(Game& game)
{
	game.game_manager().notify_all_players("Successfully entered setup round!");
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
