#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

void FileReader::load_building_cards()
{
	//Get file
	std::ifstream file("Bouwkaarten.csv");
	if (file.is_open())
	{
		BuildingCard bc;
		while(file >> bc)
		{
			buildingCards.push_back(bc);
		}
	}
	else
	{
		std::cerr << "Unable to open file\n";
	}
}

std::deque<BuildingCard>& FileReader::getBuildingCards()
{
	return this->buildingCards;
}

