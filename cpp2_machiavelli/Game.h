#pragma once
#include "GameManager.h"
#include <memory>
#include "state_machine.h"

class Game
{
public:
	Game();

	GameManager& game_manager() { return *game_manager_; }
	ClientManager& client_manager() { return *client_manager_; }
	void handle_command(ClientInfo& client_info, const std::string& command);
	
private:
	std::unique_ptr<GameManager> game_manager_;
	std::unique_ptr<ClientManager> client_manager_;
	std::unique_ptr<state_machine<Game>> state_machine_;
};

