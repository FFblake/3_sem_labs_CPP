#pragma once
#include "User.h"

// Класс туриста
class Client : public User
{
public:
	Client() {}
    Client(std::string login, std::string password, std::string name, std::string surname) : 
        User(login, password, name, surname) {};
	std::string user_type() const final {
		return "Tourist";
	}
	void Save(std::ostream& output) const override {
		User::Save(output);
	}
	void Load(std::istream& input) override {
		User::Load(input);
	}
private:
    
};


