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
	void load_decks();
	int building_card_deck_size() const { return building_card_deck_.size(); }
	int character_card_deck_size() const { return character_card_deck_.size(); }

private:
	StateMachine<Game>& state_machine_;
	FileReader file_reader_;
	std::deque<BuildingCard> building_card_deck_;
	std::deque<CharacterCard> character_card_deck_;
};

