#include "CharacterCard.h"

std::string CharacterCard::writeToConsole() const
{
	return id_ + "; " + name_;
}

void CharacterCard::readFromConsole(std::vector<std::string>& data)
{
	if (data.size() >= 2) {
		id_ = std::stoi(data.at(0));
		name_ = data.at(1);
	}
}

std::string CharacterCard::name()
{
	return name_;
}

int CharacterCard::id() const
{
	return id_;
}

std::string CharacterCard::to_string() const
{
	return "[" + std::to_string(id_) + "] " + name_ + "\r\n";
}
