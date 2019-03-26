#include "BuildingCard.h"


std::string BuildingCard::to_string()
{
	return name_.append(" (").append(color_).append(", ").append(std::to_string(points_)).append("):");
}
