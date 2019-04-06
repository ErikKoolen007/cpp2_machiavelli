#pragma once
#include "CharacterCard.h"

class King : public CharacterCard
{
public:
	King(int id, std::string name) : CharacterCard(id, name)
	{
	}
};

