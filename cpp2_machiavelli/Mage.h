#pragma once
#include "CharacterCard.h"

class Mage : public CharacterCard
{
public:
	Mage(const int id, const std::string name) : CharacterCard(id, name)
	{
	}
};

