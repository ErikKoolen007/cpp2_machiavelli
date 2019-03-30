#include "CharacterCard.h"

std::string CharacterCard::writeToConsole() const
{
	return id + "; " + name;
}

void CharacterCard::readFromConsole(std::vector<std::string>& data)
{
	if (data.size() >= 2) {
		id = data.at(0);
		name = data.at(1);
	}
}
