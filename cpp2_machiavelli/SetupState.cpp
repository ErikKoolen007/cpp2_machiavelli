#include "SetupState.h"
#include <random>

void SetupState::next()
{
}

void SetupState::setup()
{
	this->buildingCards = fileReader->load_building_cards();
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(buildingCards->begin(), buildingCards->end(), g);

}

