#pragma once
#include <string>
#include "Card.h"

class CharacterCard :
	public Card 
{
public:
	void action();
	std::string writeToConsole() const override;
	void readFromConsole(std::vector<std::string>& data) override;
	std::string name();
	std::string id();
	std::string to_string() const;
private:
	std::string id_;
	std::string name_;
};

