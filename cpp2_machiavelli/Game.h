#pragma once
#include "GameManager.h"
#include <memory>
#include "StateMachine.h"
#include "CharacterManager.h"

class Game
{
public:
	Game();

	GameManager& game_manager() { return *game_manager_; }
	ClientManager& client_manager() { return *client_manager_; }
	CharacterManager& character_manager() { return *character_manager_; }
	StateMachine<Game>& state_machine() { return *state_machine_; }

	void handle_command(ClientInfo& client_info, const std::string& command);
	
private:
	std::unique_ptr<GameManager> game_manager_;
	std::unique_ptr<ClientManager> client_manager_;
	std::unique_ptr<CharacterManager> character_manager_;
	std::unique_ptr<StateMachine<Game>> state_machine_;
};

