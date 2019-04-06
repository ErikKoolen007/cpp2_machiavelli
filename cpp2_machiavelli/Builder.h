#pragma once
#include "CharacterCard.h"

class Builder : public CharacterCard
{
public:
	Builder(int id, std::string name) : CharacterCard(id, name)
	{
	}
};

