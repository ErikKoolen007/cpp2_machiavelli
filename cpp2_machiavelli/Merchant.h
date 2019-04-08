#pragma once
#include "CharacterCard.h"

class Merchant : public CharacterCard
{
public:
	Merchant(const int id, const std::string name) : CharacterCard(id, name)
	{
	}
};

