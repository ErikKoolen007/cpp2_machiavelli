#pragma once
#include <string>
#include "BuildingCard.h"
#include "CharacterCard.h"

class Player {
public:
    Player() = default;
	Player(std::string name, int age) : name{std::move(name)}, age_{age}
	{
	}

    std::string get_name() const { return name; }
    void set_name(const std::string& new_name) { name = new_name; }

	int id() { return id_; }
	void id(int id) { id_ = id; }

	int coins() { return coins_;  }
	void coins(int coins) { coins_ = coins; }
	void add_coins(int amount) { coins_ = coins_ + amount; }

	int age() { return age_; }

	bool king() { return king_; }
	void king(bool king) { king_ = king; }

	std::vector<BuildingCard>& building_cards() { return buildings_;  }
	void add_building(BuildingCard building) { buildings_.push_back(building); }

	std::vector<std::shared_ptr<CharacterCard>>& character_cards() { return characters_; }
	void add_character(std::unique_ptr<CharacterCard> character) { characters_.emplace_back(std::move(character));  }

	std::string getInventoryInfo();
	std::string get_character_info();


private:
    std::string name;
	int age_{};
	int id_{};
	int points = 0;
	int coins_ = 0;
	bool king_ = false;
	std::vector<BuildingCard> buildings_;
	std::vector<std::shared_ptr<CharacterCard>> characters_;
	std::string get_building_info();
};
