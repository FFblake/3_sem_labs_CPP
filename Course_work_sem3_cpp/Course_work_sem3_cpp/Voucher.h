#pragma once
#include "Serializable.h"

class Voucher :public Serializable {
public:
    Voucher() {}
	Voucher(int id, std::string user_login, std::string tour_name, int visitors, int cost) :
	_id(id), _user_login(user_login), _tour_name(tour_name), _visitors(visitors), _cost(cost) {}
    void show()const {
        std::cout << "This voucher id is: " << _id << "\nThe tour is named: " << _tour_name << "\nIt is made for " << _visitors << " visitors, and costs " << _cost << "$\n";
    }
    std::string get_user_login()const {
        return _user_login;
    }
    void buy_text(int id, std::string tour_name, int visitors, int cost) const {

        std::cout << "You have bought voucher for " << tour_name << ", for " << visitors << "people, for " << cost << " $ with id= " << id<<std::endl;
    }
    int get_cost() {
        return _cost*_visitors;
    }

    void Save(std::ostream& output) const override {
        Serializable::Write(output, _id);
		Serializable::Write(output, _user_login);
		Serializable::Write(output, _tour_name);
		Serializable::Write(output, _visitors);
		Serializable::Write(output, _cost);
    }
    void Load(std::istream& input) override {
		Serializable::Read(input, _id);
		Serializable::Read(input, _user_login);
		Serializable::Read(input, _tour_name);
		Serializable::Read(input, _visitors);
		Serializable::Read(input, _cost);
    }
private:
    int _id;
    std::string _user_login;
    std::string _tour_name;
    int _visitors;
    int _cost;

};

