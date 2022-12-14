#pragma once
#include <map>
#include <string>
#include <memory>
#include "User.h"
#include "Voucher.h"
#include "Tours.h"
#include "Client.h"
#include "Worker.h"

enum UserType {
	kUndefined,
	kClient,
	kWorker,
	kAdmin
};

class TourApplication : public Serializable {
public:
    void register_client(std::string login, std::string password, std::string name, std::string surname);
    void register_worker(std::string login, std::string password, std::string name, std::string surname);
    void delete_user(std::string login);

    void register_user_as();
    UserType check_login(std::string login, std::string password);
	void change_password(std::string login, std::string old_password, std::string new_password);
	void show_user_info(std::string login);

    void create_tour(std::string name, std::string description, int duration, int tour_cost);
    void delete_tour(std::string name);
    void show_tours()const;

	int create_voucher( std::string user_login, std::string tour_name, int visitors);
	void delete_voucher(int id);
	void show_client_vouchers(std::string user_login)const;
    void show_all_vouchers()const;
	void show_sales();

	void Save(std::ostream& output) const override {
		Serializable::Write(output, _tours);
		Serializable::Write(output, _clients);
		Serializable::Write(output, _workers);
		Serializable::Write(output, _vouchers);
		Serializable::Write(output, _voucher_last_id);
	}
	void Load(std::istream& input) override {
		Serializable::Read(input, _tours);
		Serializable::Read(input, _clients);
		Serializable::Read(input, _workers);
		Serializable::Read(input, _vouchers);
		Serializable::Read(input, _voucher_last_id);
	}
private:
    int _voucher_last_id = 0;
    //User& get_user();
    
    std::map<std::string, Client> _clients;
    std::map<std::string, Worker> _workers;
    std::map<std::string, Tours> _tours;
    std::map<int, Voucher> _vouchers;
};



