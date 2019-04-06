#pragma once
#include <string>

class CharacterManager
{
public:
	CharacterManager() = default;

	std::string get_name_by_id(int char_id);
};

