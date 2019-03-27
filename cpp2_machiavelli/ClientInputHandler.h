#pragma once
#include <thread>
#include <vector>

class ClientInputHandler
{
public:
	ClientInputHandler(std::vector<std::thread>& clients) : clients(clients){}
	void handleInput();
	std::vector<std::thread>& getClients() const;
private:
	std::vector<std::thread>& clients;
};

