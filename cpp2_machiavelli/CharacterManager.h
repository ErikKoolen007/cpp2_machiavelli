#pragma once
#include <string>
#include "ClientManager.h"

class CharacterManager
{
public:
	CharacterManager(ClientManager& client_manager): client_manager_(client_manager)
	{
	}

	std::string get_name_by_id(int char_id);
	void register_special_ability_used(int player_id, int char_id);

private:
	ClientManager& client_manager_;
};

