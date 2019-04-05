#pragma once
#include "ClientManager.h"
#include "StateMachine.h"
#include <deque>
#include "FileReader.h"

class Game;

class GameManager
{
public:
	GameManager(StateMachine<Game>& state_machine) : state_machine_(state_machine)
	{
	}
	std::deque<BuildingCard>& building_cards() { return building_card_deck_; }
	std::deque<CharacterCard>& character_cards() { return character_card_deck_; }
	void load_building_deque();
	void load_character_deque();
	BuildingCard get_top_card();
	CharacterCard get_top_character_card();
	std::string get_character_card_info();
	std::deque<CharacterCard>& character_deque() { return character_card_deck_; }
	int building_card_deck_size() const { return building_card_deck_.size(); }
	int character_card_deck_size() const { return character_card_deck_.size(); }

private:
	StateMachine<Game>& state_machine_;
	FileReader file_reader_;
	std::deque<BuildingCard> building_card_deck_;
	std::deque<CharacterCard> character_card_deck_;
};

