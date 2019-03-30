#pragma once
#include <deque>
#include "BuildingCard.h"
#include "CharacterCard.h"

class FileReader
{
public:
	FileReader() = default;

	std::unique_ptr<std::deque<BuildingCard>> loadBuildingCards();
	std::unique_ptr<std::deque<CharacterCard>> loadCharacterCards();
};

