#pragma once
#include <string>
#include <utility>
#include "Card.h"

class CharacterCard : public Card 
{
public:
	CharacterCard(const int id, std::string name) : id_(id), name_(std::move(name))
	{
	}
	CharacterCard() = default;

	std::string writeToConsole() const override;
	void readFromConsole(std::vector<std::string>& data) override;

	std::string name() const;
	int id() const;
	bool dead() const { return is_dead_; }
	void kill() { is_dead_ = true; }
	bool special_used() const { return special_used_; }
	void use_special() { special_used_ = true; }
	bool robbed() const { return robbed_; }
	void rob(const int robbed_by) { robbed_ = true; robbed_by_ = robbed_by; }
	int robbed_by() const { return robbed_by_; }
	std::string to_string() const;
private:
	int id_{0};
	std::string name_;
	bool is_dead_{ false };
	bool special_used_{ false };
	bool robbed_{ false };
	int robbed_by_{ 0 };
};

