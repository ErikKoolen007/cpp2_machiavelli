//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.h"
#include <algorithm>

std::string Player::getInventoryMsg()
{
	return "\r\n Your inventory contains now: \r\n amount of points: " + 
		std::to_string(points) + "\r\n amount of coins: " + 
		std::to_string(coins_) + "\r\n " + 
		getBuildingsStr();
}

std::string Player::getBuildingsStr()
{
	std::string returnString = "buildings: \r\n";
	std::for_each(buildings_.begin(), buildings_.end(), [&](BuildingCard& building)
	{
		returnString = returnString + "- " + building.to_string() + "\r\n";
	});

	return returnString;
}

