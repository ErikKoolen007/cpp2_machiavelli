#include "GameManager.h"

ClientInputHandler& GameManager::getClientInputHandler() const
{
	return *handler;
}

void GameManager::add_client(const std::shared_ptr<ClientInfo>& client)
{
	lastPlayerId++;
	client->get_player().id(lastPlayerId);
	current_clients_.push_back(client);
}
