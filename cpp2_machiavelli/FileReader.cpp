#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::unique_ptr<std::deque<BuildingCard>> FileReader::load_building_cards()
{
	std::unique_ptr<std::deque<BuildingCard>> building_cards = std::make_unique<std::deque<BuildingCard>>();

	//Get file
	std::ifstream file("Bouwkaarten.csv");
	if (file.is_open())
	{
		BuildingCard bc;
		while(file >> bc)
		{
			building_cards->push_back(bc);
		}
		return building_cards;
	}

	std::cerr << "Unable to open file\n";
	return nullptr;
}

std::unique_ptr<std::deque<CharacterCard>> FileReader::load_character_cards()
{
	std::unique_ptr<std::deque<CharacterCard>> character_cards = std::make_unique<std::deque<CharacterCard>>();

	//Get file
	std::ifstream file("karakterkaarten.csv");
	if (file.is_open())
	{
		CharacterCard cc;
		while (file >> cc)
		{
			character_cards->push_back(cc);
		}
		return character_cards;
	}

	std::cerr << "Unable to open file\n";
	return nullptr;
}

