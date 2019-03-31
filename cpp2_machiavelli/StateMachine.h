#pragma once
#include <string>
#include <unordered_map>
#include "State.h"
#include <iostream>

template <class entity_type>
class StateMachine
{
	entity_type& owner_;

	std::string current_state_;

	std::unordered_map<std::string, std::unique_ptr<State<entity_type>>> states_{};

public:

	StateMachine(entity_type& owner) :owner_(owner) {}

	virtual ~StateMachine() = default;

	void set_current_state(std::string s) { current_state_ = s; }
	std::string current_state() const { return current_state_; }

	void handle_input(ClientInfo& client_info, const std::string& command)
	{
		if (!current_state_.empty())
			states_.at(current_state_)->handle_input(owner_, client_info, command);
	}

	void change_state(const std::string new_state)
	{
		if (states_.find(new_state) == states_.end())
		{
			std::cout << "Tried to change to undefined state.\n";
			return;
		}
		std::cout << "Changing state from: " << current_state_ << " to: " << new_state << "\n";

		states_.at(current_state_)->on_exit(owner_);
		current_state_ = new_state;
		states_.at(current_state_)->on_enter(owner_);
	}

	void addState(std::unique_ptr<State<entity_type>> state)
	{
		states_[state->name()] = std::move(state);
	}

	//returns true if the current state's type is equal to the type of the class passed as a parameter. 
	bool is_in_state(const std::string& st)const
	{
		return current_state_ == st;
	}
};
