#include "SetupState.h"

void SetupState::next()
{
}

void SetupState::setup()
{
	fileReader->load_building_cards();
	buildingCards = std::make_unique()
}

