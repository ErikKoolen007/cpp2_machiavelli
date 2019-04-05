#include "GameManager.h"
#include "Utilities.h"

void GameManager::load_building_deque()
{
	building_card_deck_ = file_reader_.load_building_cards();
	Utilities::shuffle_building_deck(building_card_deck_);
}

void GameManager::load_character_deque()
{
	character_card_deck_ = file_reader_.load_character_cards();
	Utilities::shuffle_character_deck(character_card_deck_);
}

BuildingCard GameManager::get_top_card()
{
	BuildingCard building_card = building_card_deck_.front();
	building_card_deck_.pop_front();
	return building_card;
}
