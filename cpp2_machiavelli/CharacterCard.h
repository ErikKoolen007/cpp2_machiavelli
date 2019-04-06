#pragma once
#include <string>
#include <utility>
#include "Card.h"

class CharacterCard : public Card 
{
public:
	CharacterCard(int id, std::string name) : id_(id), name_(std::move(name))
	{
	}
	CharacterCard() = default;

	std::string writeToConsole() const override;
	void readFromConsole(std::vector<std::string>& data) override;
	std::string name();
	int id() const;
	std::string to_string() const;
private:
	int id_{0};
	std::string name_;
	bool is_dead_{false};
};

