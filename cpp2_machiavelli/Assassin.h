#pragma once
#include "CharacterCard.h"
class Assassin :
	public CharacterCard
{
public:
	Assassin(int id, std::string name) : CharacterCard(id, name)
	{
	}
};

