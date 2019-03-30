#include "SetupState.h"
#include <random>

void SetupState::next()
{
}

void SetupState::setup()
{
	this->buildingCards = fileReader->loadBuildingCards();
	this->characterCards = fileReader->loadCharacterCards();
	//generate seed and shuffle buildingcards
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(buildingCards->begin(), buildingCards->end(), g);
	std::shuffle(buildingCards->begin(), buildingCards->end(), g);

	//get the clients -> werkt voor geen meter, moet herzien worden
	std::vector<std::thread>& clients = manager.getClientInputHandler().getClients();
}

