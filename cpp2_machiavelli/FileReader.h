#pragma once
#include <deque>
#include "BuildingCard.h"
#include "CharacterCard.h"

class FileReader
{
public:
private:
	std::deque<BuildingCard> buildingCards;
	std::deque<CharacterCard> characterCard;
};

