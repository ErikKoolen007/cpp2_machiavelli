#pragma once
#include <deque>
#include "BuildingCard.h"
#include "CharacterCard.h"

class FileReader
{
public:
	FileReader() = default;

	std::deque<BuildingCard> load_building_cards() const;
	std::deque<std::unique_ptr<CharacterCard>> load_character_cards() const;
};

