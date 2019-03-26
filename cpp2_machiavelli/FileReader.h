#pragma once
#include <deque>
#include "BuildingCard.h"
#include "CharacterCard.h"

class FileReader
{
public:
	FileReader() = default;

	void load_building_cards();
	std::deque<BuildingCard>& getBuildingCards();
private:
	std::deque<BuildingCard> buildingCards;
	std::deque<CharacterCard> characterCards;

};

