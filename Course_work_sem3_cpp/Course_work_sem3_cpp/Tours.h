#pragma once
#include "Serializable.h"

class Tours : public Serializable
{   
public:
    Tours() {}
	Tours(std::string name, std::string description, int duration, int tour_cost) :
		_name(name), _description(description), _duration(duration), _tour_cost(tour_cost) {}
    void show() const {
		std::cout << "Tour name is: " << _name << "\nDescription: "
			<< _description << "\nDuration is: " << _duration<<"\nCost is: "<<_tour_cost << std::endl;
    }
    int get_cost() const{
        return _tour_cost;
    }
    std::string get_name() const {
        return _name;
    }
	void Save(std::ostream& output) const override {
		Serializable::Write(output, _name);
		Serializable::Write(output, _description);
		Serializable::Write(output, _duration);
        Serializable::Write(output, _tour_cost);
	}
	void Load(std::istream& input) override {
		Serializable::Read(input, _name);
		Serializable::Read(input, _description);
		Serializable::Read(input, _duration);
		Serializable::Read(input, _tour_cost);
	}
private:
    std::string _name;
    std::string _description;
    int _duration;
    int _tour_cost;
};

