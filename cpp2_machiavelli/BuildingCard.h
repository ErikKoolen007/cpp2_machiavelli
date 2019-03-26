#pragma once
#include <string>
#include <utility>
#include <sstream>
#include <vector>
#include <iostream>

class BuildingCard
{
public:
	BuildingCard() = default;
	BuildingCard(std::string name, int points, std::string color) : name_(std::move(name)), 
																	points_(points), color_(std::move(color))
	{
	}

	std::string name() const { return name_; }
	int points() const { return points_; }
	std::string color() const { return color_; }
	std::string description() const { return description_; }
	void name(const std::string& n) { name_ = n; }
	void points(int p) { points_ = p; }
	void color(const std::string& c) { color_ = c; }
	void description(const std::string & d) { description_ = d; }

	void special_power();
	std::string to_string();
private:
	std::string name_;
	int points_ = 0;
	std::string color_;
	std::string description_ = "";
};

inline std::ostream& operator<<(std::ostream& os, const BuildingCard& bc)
{
	return os << bc.name() << " (" << bc.color() << ", " << bc.points() << "):";
}

inline std::istream& operator>>(std::istream& is, BuildingCard& bc)
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

	if (data.size() >= 3) {
		bc.name(data.at(0));
		bc.points(std::stoi(data.at(1)));
		bc.color(data.at(2));
	}
	if(data.size() == 4)
	{
		bc.description(data.at(3));
	}

	return is;
}


