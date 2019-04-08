#pragma once
#include "CharacterCard.h"

class Thief : public CharacterCard
{
public:
	Thief(const int id, const std::string name) : CharacterCard(id, name)
	{
	}
};

