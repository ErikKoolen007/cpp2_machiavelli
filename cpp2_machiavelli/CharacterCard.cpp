#include "CharacterCard.h"

std::string CharacterCard::writeToConsole() const
{
	return id_ + "; " + name_;
}

void CharacterCard::readFromConsole(std::vector<std::string>& data)
{
	if (data.size() >= 2) {
		id_ = data.at(0);
		name_ = data.at(1);
	}
}

std::string CharacterCard::name()
{
	return name_;
}

std::string CharacterCard::id()
{
	return id_;
}
