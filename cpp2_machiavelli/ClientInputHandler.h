#pragma once
#include "ClientInfo.h"

class ClientInputHandler
{
public:
	ClientInputHandler() = default;
	void handleInput(ClientInfo& client_info, const std::string& command);

private:
};

