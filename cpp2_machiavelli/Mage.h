#pragma once
#include "CharacterCard.h"
class Mage :
	public CharacterCard
{
public:
	Mage(int id, std::string name) : CharacterCard(id, name)
	{
	}
};

