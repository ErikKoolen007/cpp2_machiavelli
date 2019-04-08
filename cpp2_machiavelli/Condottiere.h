#pragma once
#include "CharacterCard.h"

class Condottiere : public CharacterCard
{
public:
	Condottiere(const int id, const std::string name) : CharacterCard(id, name)
	{
	}
};

