#pragma once
#include "User.h"

class Worker : public User
{
public:
	Worker(){}
	Worker(std::string login, std::string password, std::string name, std::string surname):
		User(login, password, name, surname) {};
	std::string user_type() const final {
		return "Worker";
	}
	void Save(std::ostream& output) const override {
		User::Save(output);
	}
	void Load(std::istream& input) override {
		User::Load(input);
	}
private:
	
};


