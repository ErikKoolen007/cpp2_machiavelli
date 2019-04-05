#pragma once
#include "CharacterCard.h"
class Merchant :
	public CharacterCard
{
public:
	Merchant(int id, std::string name) : CharacterCard(id, name)
	{
	}
};

