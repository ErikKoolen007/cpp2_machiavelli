#include "BuildingCard.h"


std::string BuildingCard::to_string()
{
	return name_.append(" (").append(color_).append(", ").append(std::to_string(points_)).append("):");
}

std::string BuildingCard::writeToConsole() const
{
	return name_ + " (" + color_ + ", " + std::to_string(points_) + "):";
}

void BuildingCard::readFromConsole(std::vector<std::string>& data)
{

	if (data.size() >= 3) {
		name_ = data.at(0);
		color_ = data.at(2);
}
if (data.size() == 4)
{
	description_ = data.at(3);
}
}
