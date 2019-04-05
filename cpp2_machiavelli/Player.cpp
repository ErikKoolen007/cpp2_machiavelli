//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.h"
#include <algorithm>

std::string Player::getInventoryInfo()
{
	return "\r\n Your inventory contains now: \r\n amount of points: " + 
		std::to_string(points) + "\r\n amount of coins: " + 
		std::to_string(coins_) + "\r\n " + 
		getBuildingInfo();
}

std::string Player::getCharacterInfo()
{
	if(characters_.empty())
	{
		return "\r\n\There are no chracters assigned to you yet \r\n";
	}

	std::string return_string = "\r\n\You are the following characters: \r\n";
	std::for_each(characters_.begin(), characters_.end(), [&](CharacterCard& character)
	{
		return_string = return_string + "- " + character.to_string() + "\r\n";
	});

	return return_string;
}

std::string Player::getBuildingInfo()
{
	std::string return_string = "\r\n\You have the following buildings: \r\n";
	std::for_each(buildings_.begin(), buildings_.end(), [&](BuildingCard& building)
	{
		return_string = return_string + "- " + building.to_string() + "\r\n";
	});

	return return_string;
}

