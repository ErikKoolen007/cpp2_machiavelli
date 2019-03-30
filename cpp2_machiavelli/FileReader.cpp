#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::unique_ptr<std::deque<BuildingCard>> FileReader::loadBuildingCards()
{
	std::unique_ptr<std::deque<BuildingCard>> buildingCards;
	buildingCards = std::make_unique<std::deque<BuildingCard>>();
	//Get file
	std::ifstream file("Bouwkaarten.csv");
	if (file.is_open())
	{
		BuildingCard bc;
		while(file >> bc)
		{
			buildingCards->push_back(bc);
		}
		return buildingCards;
	}

	std::cerr << "Unable to open file\n";
	return nullptr;
}

std::unique_ptr<std::deque<CharacterCard>> FileReader::loadCharacterCards()
{
	std::unique_ptr<std::deque<CharacterCard>> characterCards;
	characterCards = std::make_unique<std::deque<CharacterCard>>();
	//Get file
	std::ifstream file("karakterkaarten.csv");
	if (file.is_open())
	{
		CharacterCard cc;
		while (file >> cc)
		{
			characterCards->push_back(cc);
		}
		return characterCards;
	}

	std::cerr << "Unable to open file\n";
	return nullptr;
}

