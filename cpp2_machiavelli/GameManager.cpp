#include "GameManager.h"

ClientInputHandler& GameManager::getClientInputHandler() const
{
	return *handler;
}
