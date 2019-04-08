#pragma once
#include "CharacterCard.h"

class King : public CharacterCard
{
public:
	King(const int id, const std::string name) : CharacterCard(id, name)
	{
	}
};

