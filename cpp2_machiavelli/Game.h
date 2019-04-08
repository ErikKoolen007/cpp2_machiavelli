#pragma once
#include "GameManager.h"
#include <memory>
#include "StateMachine.h"
#include "CharacterManager.h"

class Game
{
public:
	Game();

	GameManager& game_manager() const { return *game_manager_; }
	ClientManager& client_manager() const { return *client_manager_; }
	CharacterManager& character_manager() const { return *character_manager_; }
	StateMachine<Game>& state_machine() const { return *state_machine_; }

	void handle_command(ClientInfo& client_info, const std::string& command) const;
	
private:
	std::unique_ptr<GameManager> game_manager_;
	std::unique_ptr<ClientManager> client_manager_;
	std::unique_ptr<CharacterManager> character_manager_;
	std::unique_ptr<StateMachine<Game>> state_machine_;
};

