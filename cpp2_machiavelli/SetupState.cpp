#include "SetupState.h"
#include <random>

void SetupState::next()
{
}

void SetupState::setup()
{
	this->building_cards_ = file_reader_->load_building_cards();
	this->character_cards_ = file_reader_->load_character_cards();
	//generate seed and shuffle buildingcards
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(building_cards_->begin(), building_cards_->end(), g);
}

