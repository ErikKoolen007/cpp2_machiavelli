#pragma once
#include <vector>
#include "Player.h"
#include <deque>

class Turn
{
public:
private:
	std::vector<Player> players;
	std::deque<BuildingCard> buildingCards;
};

