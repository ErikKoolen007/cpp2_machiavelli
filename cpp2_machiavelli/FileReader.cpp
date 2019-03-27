#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::unique_ptr<std::deque<BuildingCard>> FileReader::load_building_cards()
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

