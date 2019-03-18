#pragma once

#include <string>
#include <utility>

class Player {
public:
    Player() = default;
	Player(std::string name) : name_ {std::move(name)}
	{
	}

    std::string get_name() const { return name_; }
    void set_name(const std::string& new_name) { name_ = new_name; }

private:
    std::string name_;
	int points_ = 0;
	int coins_ = 0;
};
