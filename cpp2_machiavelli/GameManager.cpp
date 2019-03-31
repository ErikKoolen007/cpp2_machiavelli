#include "GameManager.h"
#include "Utilities.h"

void GameManager::load_decks()
{
	building_card_deck_ = file_reader_.load_building_cards();
	Utilities::shuffle_building_deck(building_card_deck_);

	character_card_deck_ = file_reader_.load_character_cards();
	Utilities::shuffle_character_deck(character_card_deck_);
}
