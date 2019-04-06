#include "CharacterManager.h"

std::string CharacterManager::get_name_by_id(int char_id)
{
	switch (char_id)
	{
	case 1:
		return "Assassin";
	case 2:
		return "Thief";
	case 3:
		return "Mage";
	case 4:
		return "King";
	case 5:
		return "Preacher";
	case 6:
		return "Merchant";
	case 7:
		return "Builder";
	case 8:
		return "Condottiere";
	default: 
		return "Unknown";
	}
}
