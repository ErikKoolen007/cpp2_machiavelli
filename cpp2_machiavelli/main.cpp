#include <iostream>
#include "Server.h"

int main()
{
	//new int();
	{
		Server server;
		server.init();
	}

	//Memory check
	std::cout << "\nMemory leaks? (0 for no, 1 for yes. See output for details.)" << _CrtDumpMemoryLeaks() << std::endl;

    return 0;
}

