#pragma once
#include <string>
#include <utility>
#include <sstream>
#include <vector>
#include <iostream>

class Card
{
public:
	virtual ~Card() = default;
	virtual std::string writeToConsole() const = 0;
	virtual void readFromConsole(std::vector<std::string>&) = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Card& card)
{
	std::string outputString = card.writeToConsole();
	
	return os << outputString;
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

	return is;
}

