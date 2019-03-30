#pragma once
#include <string>
#include <utility>
#include <sstream>
#include <vector>
#include <iostream>

class Card
{
public:
	virtual std::string writeToConsole() const = 0;
	virtual void readFromConsole(std::vector<std::string>&) = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Card& card)
{
	std::string outputString = card.writeToConsole();
	return os << outputString;
	//return os << bc.name() << " (" << bc.color() << ", " << bc.points() << "):";
}

inline std::istream& operator>>(std::istream& is, Card& card)
{
	std::string line;
	std::getline(is, line);

	std::stringstream lineStream(line);
	std::string cell;
	std::vector<std::string> data;

	while (std::getline(lineStream, cell, ';'))
	{
		data.push_back(cell);
	}

	card.readFromConsole(data);
	// if (data.size() >= 3) {
	// 	bc.name(data.at(0));
	// 	bc.points(std::stoi(data.at(1)));
	// 	bc.color(data.at(2));
	// }
	// if (data.size() == 4)
	// {
	// 	bc.description(data.at(3));
	// }

	return is;
}

