#pragma once

#include <string>
#include <utility>
#include <vector>
#include "BuildingCard.h"
#include "CharacterCard.h"

class Player {
public:
    Player() = default;
	Player(std::string name, int age) : name{ std::move(name) }, age_{age}
	{
	}

    std::string get_name() const { return name; }
    void set_name(const std::string& new_name) { name = new_name; }
	int id() { return id_; }
	void id(int id) { id_ = id; }
	int age() { return age_; }
	bool king() { return king_; }
	void king(bool king) { king_ = king; }

private:
    std::string name;
	int age_;
	int id_;
	int points = 0;
	int coins = 0;
	bool king_ = false;
	std::vector<BuildingCard> buildings;
	CharacterCard character;
};
