#pragma once
#include <string>
#include "Serializable.h"

// Общий класс для пользователя
class User : public Serializable
{  
protected:
	User (){}
	User(std::string login, std::string password, std::string name, std::string surname)
		: Serializable(), _login(login), _password(password), _name(name), _surname(surname){}


public:
    std::string get_login() const {
        return _login;
        
    }
	int verify_password(std::string password) const {
		if (_password == password) {
			return 1;
		}
		else {
			throw std::domain_error ("Wrong password during logging");
		}
		return 0;
	}
    void change_user_password(std::string old_password, std::string new_password)  {
        if (old_password != _password)
            throw std::domain_error("Incorrect old password");
        _password = new_password;
    }
    void show_user_info() const {
        std::cout << _name << " " << _surname << std::endl;
    }

    virtual std::string user_type() const = 0;
	void Save(std::ostream& output) const override {
		Serializable::Write(output, _login);
		Serializable::Write(output, _password);
        Serializable::Write(output, _name);
		Serializable::Write(output, _surname);
	}
	void Load(std::istream& input) override {
		Serializable::Read(input, _login);
		Serializable::Read(input, _password);
		Serializable::Read(input, _name);
		Serializable::Read(input, _surname);
	}
private:
	std::string _login;
	std::string _password;
	std::string _name;
	std::string _surname;
};



