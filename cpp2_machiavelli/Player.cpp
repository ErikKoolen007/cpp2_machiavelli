//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.h"
#include <algorithm>

void Player::remove_hand_buildings(int amount)
{
	if (amount > 0 && static_cast<unsigned>(amount) <= building_cards().size())
		building_cards().erase(building_cards().begin(), building_cards().begin() + amount);
}

void Player::destroy_building(int index)
{
	if(building_cards_on_table().size() > static_cast<unsigned>(index) && index >= 0)
		building_cards_on_table().erase(building_cards_on_table().begin() + index);
}

std::shared_ptr<CharacterCard>& Player::character_card(int character_id)
{
	return *std::find_if(characters_.begin(), characters_.end(), 
		[&](auto& character) {return character->id() == character_id; });
}

bool Player::has_character_card(int character_id)
{
	const auto characters_ptr = std::find_if(characters_.begin(), characters_.end(),
		[&](auto& character) {return character->id() == character_id; });

	return characters_ptr != std::end(characters_);
}

void Player::clear_characters()
{
	characters_.clear();
}

std::string Player::getInventoryInfo()
{
	return "\r\n Your inventory contains now: \r\n amount of points: " + 
		std::to_string(points_) + "\r\n amount of coins: " + 
		std::to_string(coins_) + "\r\n " + 
		get_building_info();
}

std::string Player::get_character_info()
{
	if(characters_.empty())
	{
		return "\r\n\There are no characters assigned to you yet \r\n";
	}

	std::string return_string = "\r\n\You are the following characters: \r\n";
	std::for_each(characters_.begin(), characters_.end(), [&](std::shared_ptr<CharacterCard>& character)
	{
		return_string = return_string + "- " + character->to_string() + "\r\n";
	});

	return return_string;
}

std::string Player::get_building_info()
{
	std::string return_string = "\r\n\You have the following buildings: \r\n";
	std::for_each(buildings_.begin(), buildings_.end(), [&](BuildingCard& building)
	{
		return_string = return_string + "- " + building.to_string() + "\r\n";
	});

	return return_string;
}

