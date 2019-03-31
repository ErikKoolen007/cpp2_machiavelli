#include "Utilities.h"
#include <random>
#include <chrono>

int Utilities::random_number(int min, int max)
{
	const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	const std::uniform_int_distribution<int> distribution(min, max);

	return distribution(generator);
}

void Utilities::shuffle_building_deck(std::deque<BuildingCard>& deck)
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(deck.begin(), deck.end(), g);
}

void Utilities::shuffle_character_deck(std::deque<CharacterCard>& deck)
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(deck.begin(), deck.end(), g);
}
