#pragma once
#include <deque>
#include "BuildingCard.h"
#include "CharacterCard.h"

class FileReader
{
public:
	FileReader() = default;

	std::unique_ptr<std::deque<BuildingCard>> load_building_cards();
	std::unique_ptr<std::deque<CharacterCard>> load_character_cards();
};

