#include "CharacterManager.h"
#include <algorithm>

std::string CharacterManager::get_name_by_id(int char_id) const
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

void CharacterManager::register_special_ability_used(int player_id, int char_id)
{
	//Get player
	auto& client = client_manager_.get_client(player_id);

	//Check each card
	std::for_each(client.get_player().character_cards().begin(), client.get_player().character_cards().end(),
		[&](std::shared_ptr<CharacterCard>& char_card)
	{
		//Character uses his special
		if (char_card->id() == char_id)
		{
			char_card->use_special();
		}
	});
}
