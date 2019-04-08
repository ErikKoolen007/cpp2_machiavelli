#pragma once
#include "CharacterCard.h"

class Assassin : public CharacterCard
{
public:
	Assassin(const int id, const std::string name) : CharacterCard(id, name)
	{
	}
};

