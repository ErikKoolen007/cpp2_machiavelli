#include "FileReader.h"
#include <fstream>
#include <iostream>

std::deque<BuildingCard> FileReader::load_building_cards()
{
	std::deque<BuildingCard> building_cards;

	//Get file
	std::ifstream file("Bouwkaarten.csv");
	if (file.is_open())
	{
		BuildingCard bc;
		while(file >> bc)
		{
			building_cards.push_back(bc);
		}

		return building_cards;
	}

	std::cerr << "Unable to open file\n";
	return building_cards;
}

std::deque<CharacterCard> FileReader::load_character_cards()
{
	std::deque<CharacterCard> character_cards;

	//Get file
	std::ifstream file("karakterkaarten.csv");
	if (file.is_open())
	{
		CharacterCard cc;
		while (file >> cc)
		{
			//king is not implemented as a card
			if(cc.id() != 4)
			{
				character_cards.push_back(cc);
			}
		}

		return character_cards;
	}

	std::cerr << "Unable to open file\n";
	return character_cards;
}

