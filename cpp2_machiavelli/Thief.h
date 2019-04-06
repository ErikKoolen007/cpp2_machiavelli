#pragma once
#include "CharacterCard.h"

class Thief : public CharacterCard
{
public:
	Thief(int id, std::string name) : CharacterCard(id, name)
	{
	}
};

