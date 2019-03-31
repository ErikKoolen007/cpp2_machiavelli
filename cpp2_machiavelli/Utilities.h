#pragma once
#include <deque>
#include "BuildingCard.h"
#include "CharacterCard.h"

class Utilities
{
public:
	static int random_number(int min, int max);

	//TODO make this more generic XD
	static void shuffle_building_deck(std::deque<BuildingCard>& deck);
	static void shuffle_character_deck(std::deque<CharacterCard>& deck);
private:
	Utilities() = default;
};

