#pragma once
#include <string>
#include <utility>
#include <vector>
#include "Card.h"

class BuildingCard :
	public Card
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
	std::string to_string() const;
	std::string writeToConsole() const override;
	void readFromConsole(std::vector<std::string>&) override;
private:
	std::string name_;
	int points_ = 0;
	std::string color_;
	std::string description_ = "";
};


