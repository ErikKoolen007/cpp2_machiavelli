#include "ClientInputHandler.h"

std::vector<std::thread>& ClientInputHandler::getClients() const
{
	return clients;
}
