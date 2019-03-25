#pragma once
#include <thread>
#include <vector>

class ClientInputHandler
{
public:
	ClientInputHandler(std::vector<std::thread>& clients) : clients(clients){}
	void handleInput();
private:
	std::vector<std::thread>& clients;
};

