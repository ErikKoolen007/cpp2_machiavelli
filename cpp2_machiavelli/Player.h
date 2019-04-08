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

	int id() const { return id_; }
	void id(int id) { id_ = id; }

	int points() const { return points_; }
	void add_points(int points) { points_ += points; }

	int building_card_points() const { return building_card_points_; }
	void add_building_card_points(int points) { building_card_points_ += points; }

	int coins() const { return coins_;  }
	void coins(int coins) { coins_ = coins; }
	void add_coins(int amount) { coins_ = coins_ + amount; }

	int age() const { return age_; }

	bool king() const { return king_; }
	void king(bool king) { king_ = king; }

	bool first_full_city() const { return first_full_city_; }
	void build_full_city() { first_full_city_ = true; }

	std::vector<BuildingCard>& building_cards() { return buildings_;  }
	void add_building(BuildingCard building) { buildings_.push_back(building); }
	void remove_hand_buildings(int amount);

	std::vector<BuildingCard>& building_cards_on_table() { return buildings_on_table_; }
	void transfer_buildings_to_table(std::string building_name);
	void add_building_to_table(BuildingCard building) { buildings_on_table_.push_back(building); }
	void destroy_building(int index);

	std::vector<std::shared_ptr<CharacterCard>>& character_cards() { return characters_; }
	std::shared_ptr<CharacterCard>& character_card(int character_id);
	bool has_character_card(int character_id);
	void add_character(std::unique_ptr<CharacterCard> character) { characters_.emplace_back(std::move(character));  }
	void clear_characters();

	std::string getInventoryInfo();
	std::string get_character_info();
	std::string get_played_buildings_info();
	std::string get_building_info();

	void reset();

private:
    std::string name;
	int age_{};
	int id_{};
	int points_ = 0;
	int building_card_points_ = 0;
	int coins_ = 0;
	bool king_ = false;
	bool first_full_city_{ false };
	std::vector<BuildingCard> buildings_;
	std::vector<BuildingCard> buildings_on_table_;
	std::vector<std::shared_ptr<CharacterCard>> characters_;
};
