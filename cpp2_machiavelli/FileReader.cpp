#include "FileReader.h"
#include <fstream>
#include <iostream>
#include "Assassin.h"
#include "Thief.h"
#include "Mage.h"
#include "Preacher.h"
#include "Merchant.h"
#include "Builder.h"
#include "Condotierre.h"

class Assassin;

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

std::deque<std::unique_ptr<CharacterCard>> FileReader::load_character_cards()
{
	std::deque<std::unique_ptr<CharacterCard>> character_cards;

	//Get file
	std::ifstream file("karakterkaarten.csv");
	if (file.is_open())
	{
		CharacterCard cc;
		while (file >> cc)
		{
			switch (cc.id())
			{
			case 1:
				character_cards.push_back(std::make_unique<Assassin>(cc.id(), cc.name()));
				break;
			case 2:
				character_cards.push_back(std::make_unique<Thief>(cc.id(), cc.name()));
				break;
			case 3:
				character_cards.push_back(std::make_unique<Mage>(cc.id(), cc.name()));
				break;
			//case 4: king is not implemented in the deck
			case 5:
				character_cards.push_back(std::make_unique<Preacher>(cc.id(), cc.name()));
				break;
			case 6:
				character_cards.push_back(std::make_unique<Merchant>(cc.id(), cc.name()));
				break;
			case 7:
				character_cards.push_back(std::make_unique<Builder>(cc.id(), cc.name()));
				break;
			case 8:
				character_cards.push_back(std::make_unique<Condotierre>(cc.id(), cc.name()));
				break;
			default: 
				std::cerr << "Unknown character: " << cc.id() << "| " << cc.name() << "\n";
			}
		}
		
		return character_cards;
	}

	std::cerr << "Unable to open file\n";
	return character_cards;
}

