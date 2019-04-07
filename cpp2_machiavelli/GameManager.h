#pragma once
#include "ClientManager.h"
#include "StateMachine.h"
#include <deque>
#include "FileReader.h"
#include <queue>

class Game;

class GameManager
{
public:
	GameManager(StateMachine<Game>& state_machine) : state_machine_(state_machine)
	{
	}
	std::deque<BuildingCard>& building_cards() { return building_card_deck_; }
	std::deque<std::unique_ptr<CharacterCard>>& character_cards() { return character_card_deck_; }
	void load_building_deque();
	void load_character_deque();
	int pop_character_order_queue();
	int get_character_order_queue_size() const { return character_order_queue_.size(); }
	BuildingCard get_top_building_card();
	std::unique_ptr<CharacterCard> get_top_character_card();
	std::unique_ptr<CharacterCard> get_character_card(int id);
	std::string get_character_card_info();
	int building_card_deck_size() const { return building_card_deck_.size(); }
	int character_card_deck_size() const { return character_card_deck_.size(); }
	std::queue<int>& get_character_order_queue() { return character_order_queue_; }
private:
	StateMachine<Game>& state_machine_;
	FileReader file_reader_;
	std::deque<BuildingCard> building_card_deck_;
	std::deque<std::unique_ptr<CharacterCard>> character_card_deck_;
	std::queue<int> character_order_queue_;
	void load_character_order_queue();
};

