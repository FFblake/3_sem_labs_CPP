#include "TourApplication.h"
#include "Client.h"
#include "Worker.h"
#include "Voucher.h"



void TourApplication::register_client(std::string login, std::string password, std::string name, std::string surname)
{
	auto user = Client (login, password, name, surname);
	auto it = _clients.find(login);
	auto it2 = _workers.find(login);
	if ((it != _clients.end())&&(it2 != _workers.end())) {
		throw std::domain_error("User with this login already exists");
	}
	_clients.insert({ login, user });
}

void TourApplication::register_worker(std::string login, std::string password, std::string name, std::string surname)
{
	auto user = Worker(login, password, name, surname);
	auto it = _clients.find(login);
	auto it2 = _workers.find(login);
	if ((it != _clients.end() && it2 != _workers.end())) {
		throw std::domain_error("User with this login already exists");
	}
	_workers.insert({ login, user });
}


void TourApplication::delete_user(std::string login)
{
	auto it = _clients.find(login);
	auto it2 = _workers.find(login);
	if (it == _clients.end() && it2 == _workers.end()) {
		throw std::domain_error("User with this login doesn't exists");
	}
	else if (it == _clients.end())
		_workers.erase(it2);
	else
		_clients.erase(it);
}

UserType TourApplication::check_login(std::string login, std::string password)
{
	int pass;
	auto it = _clients.find(login);
	if (it != _clients.end()) {
		pass = it->second.verify_password(password);
		if (pass == 1)
			return UserType::kClient;
	}

	auto it2 = _workers.find(login);
	if (it2 != _workers.end()) {
		pass = it2->second.verify_password(password);
		if (it2->second.verify_password(password) == 1) {
			if (login == "Admin")
				return UserType::kAdmin;
			return UserType::kWorker;
		}
	}
	return UserType::kUndefined;
}

void TourApplication::change_password(std::string login, std::string old_password, std::string new_password)
{
	auto it = _clients.find(login);
	if (it != _clients.end()) {
		it->second.change_user_password(old_password, new_password);
			return;
	}

	auto it2 = _workers.find(login);
	if (it2 != _workers.end()) {
		it->second.change_user_password(old_password, new_password);
			return ;
		
	}
}

void TourApplication::show_user_info(std::string login)
{
	auto it = _clients.find(login);
	if (it != _clients.end()) {
		it->second.show_user_info();
		return;
	}

	auto it2 = _workers.find(login);
	if (it2 != _workers.end()) {
		it2->second.show_user_info();
		return;
	}
	throw std::domain_error("No users found");
}



void TourApplication::create_tour(std::string name, std::string description, int duration, int tour_cost) 
{
	auto result = _tours.insert({ name, Tours(name, description, duration, tour_cost) });
	if (result.second == false) {
		throw std::domain_error("Tour with this name already exists");
	};
}

void TourApplication::delete_tour(std::string name) {
	auto it = _tours.find(name);
	if (it == _tours.end()) {
		throw std::domain_error("No such tour found");
	}
	_tours.erase(it);
}

void TourApplication::show_tours()const {
	for (auto it = _tours.begin(); it != _tours.end(); ++it) {
		it->second.show();
	}
	std::cout << std::endl;
}

int TourApplication::create_voucher ( std::string user_login, std::string tour_name, int visitors){
	auto it = _clients.find(user_login);
	if (it == _clients.end()) {
		throw std::domain_error("Client with this login doesn't exists");
	}

	auto it2 = _tours.find(tour_name);
	if (it2 == _tours.end()) {
		throw std::domain_error("No such tour found");
	}
	int voucher_cost = it2->second.get_cost() * visitors;

	const auto new_voucher_id = ++_voucher_last_id;
	_vouchers[new_voucher_id] = Voucher(new_voucher_id, user_login, tour_name, visitors, voucher_cost);

	return new_voucher_id;
}
void TourApplication::delete_voucher(int id) {
	auto it = _vouchers.find(id);
	if (it == _vouchers.end()) {
		throw std::domain_error("No such voucher found");
	}
	_vouchers.erase(it);
}


void TourApplication::show_client_vouchers(std::string user_login)const {
	auto it = _clients.find(user_login);
	if (it == _clients.end()) {
		throw std::domain_error("No such user found");
	}
	for (auto it2 = _vouchers.begin(); it2 != _vouchers.end(); ++it2) {
		if (it2->second.get_user_login() ==user_login) {
			it2->second.show();
		}
	}
}
void TourApplication::show_all_vouchers()const {
	for (auto it2 = _vouchers.begin(); it2 != _vouchers.end(); ++it2) {
			it2->second.show();
	}
}
void TourApplication::show_sales() {
	int sum = 0;
	for (auto it2 = _vouchers.begin(); it2 != _vouchers.end(); ++it2) {
		sum+=it2->second.get_cost();
	}
	std::cout << "Current sum of sales is: " << sum << "$\n";
	return;
}