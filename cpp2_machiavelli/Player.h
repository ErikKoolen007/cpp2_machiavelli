#pragma once

#include <string>
#include <utility>
#include <vector>
#include "BuildingCard.h"
#include "CharacterCard.h"

class Player {
public:
    Player() = default;
	Player(std::string name) : name {std::move(name)}
	{
	}

    std::string get_name() const { return name; }
    void set_name(const std::string& new_name) { name = new_name; }

private:
    std::string name;
	int points = 0;
	int coins = 0;
	std::vector<BuildingCard> buildings;
	CharacterCard character;
};
