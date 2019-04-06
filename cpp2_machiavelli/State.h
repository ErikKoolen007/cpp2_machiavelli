#pragma once
#include <string>
#include "ClientInfo.h"

template <class object_type>
class State
{
public:
	virtual ~State() = default;
	virtual void on_enter(object_type& game) = 0;
	virtual void handle_input(object_type& game, ClientInfo& client, const std::string& command) = 0;
	virtual void on_exit(object_type& game) = 0;
	virtual std::string name() = 0;
};

