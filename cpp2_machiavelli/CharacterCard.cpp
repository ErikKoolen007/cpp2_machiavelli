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

std::string CharacterCard::to_string() const
{
	if(name_ == "")
	{
		return "There is no character assigned to you yet";
	}
	return "Your current character is" + name_;
}
