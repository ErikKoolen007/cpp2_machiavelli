#pragma once
#include "CharacterCard.h"

class Builder : public CharacterCard
{
public:
	Builder(const int id, const std::string name) : CharacterCard(id, name)
	{
	}
};

