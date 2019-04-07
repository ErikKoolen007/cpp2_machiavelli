#include "GameManager.h"
#include "Utilities.h"
#include <algorithm>

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

void GameManager::load_character_order_queue()
{
	//4 -3 -2 - 1 - 5 - 6 - 7 - 8
	character_order_queue_.push(4);
	character_order_queue_.push(1);
	character_order_queue_.push(2);
	character_order_queue_.push(3);
	character_order_queue_.push(5);
	character_order_queue_.push(6);
	character_order_queue_.push(7);
	character_order_queue_.push(8);
}

int GameManager::pop_character_order_queue()
{
	if(character_order_queue_.empty())
	{
		load_character_order_queue();
	}
	int character_id = character_order_queue_.front();
	character_order_queue_.pop();
	return character_id;
}

BuildingCard GameManager::get_top_building_card()
{
	BuildingCard building_card = building_card_deck_.front();
	building_card_deck_.pop_front();
	return building_card;
}

std::unique_ptr<CharacterCard> GameManager::get_top_character_card()
{
	std::unique_ptr<CharacterCard> character_card = std::move(character_card_deck_.front());
	character_card_deck_.pop_front();
	
	return character_card;
}

std::unique_ptr<CharacterCard> GameManager::get_character_card(int id)
{
	for (auto it = character_card_deck_.begin(); it != character_card_deck_.end(); ++it) {
		std::unique_ptr<CharacterCard>& element = *it;
		
		if ( element != nullptr && element->id() == id)
		{
			std::unique_ptr<CharacterCard> moved = std::move(*it);
			character_card_deck_.erase(it);
			return moved;
		} 
	}
	return nullptr;
}

std::string GameManager::get_character_card_info()
{
	std::string return_string = "";
	std::for_each(character_card_deck_.begin(), character_card_deck_.end(), [&](std::unique_ptr<CharacterCard>& character_card)
	{
		return_string = return_string + character_card->to_string();
	});
	return return_string;
}


