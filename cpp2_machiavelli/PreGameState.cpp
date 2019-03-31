#include "PreGameState.h"

void PreGameState::on_enter(Game& game)
{
}

void PreGameState::handle_input(Game& game, ClientInfo& client_info, const std::string& command)
{
	auto &client = client_info.get_socket();
	auto &player = client_info.get_player();
	client << player.get_name() << ", id: " << player.id() << ", you wrote: '" << command
		<< "' in: " << name() << ", but I'll ignore that for now.\r\n" << "machiavelli> ";
}

void PreGameState::on_exit(Game& game)
{
}

std::string PreGameState::name()
{
	return "PreGameState";
}
