#pragma once
#include "GameManager.h"

class CharacterManager
{
public:
	CharacterManager(GameManager& game_manager, ClientManager& client_manager): game_manager_(game_manager), client_manager_(client_manager)
	{
		
	}

	void special_power(int char_id);
private:
	GameManager& game_manager_;
	ClientManager& client_manager_;
};

