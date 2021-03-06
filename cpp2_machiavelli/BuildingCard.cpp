#include "BuildingCard.h"


std::string BuildingCard::to_string() const
{
	return name_ + " (" + color_ + ", " + std::to_string(points_) + "):";
}

std::string BuildingCard::writeToConsole() const
{
	return name_ + " (" + color_ + ", " + std::to_string(points_) + "):";
}

void BuildingCard::readFromConsole(std::vector<std::string>& data)
{

	if (data.size() >= 3) {
		name_ = data.at(0);
		points_ = std::stoi(data.at(1));
		color_ = data.at(2);
	}
	if (data.size() == 4)
	{
		description_ = data.at(3);
	}
}
