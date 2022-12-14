#pragma once
#include "TourApplication.h"
#include <vector>

class Menu 
{
public:
    Menu(TourApplication &app) : _app(app) { }

	void Login() {
		std::string login, password, name, surname;
		std::cout << "Please enter your login: ";
        std::getline(std::cin >> std::ws, login);
		std::cout << "Enter password: ";
        std::getline(std::cin >> std::ws, password);
        
        auto user_type = _app.check_login(login, password);
        if (user_type == kUndefined) {
            RegisterClient(login, password);
            user_type = kClient;
        }
        std::cout << "User logged successfully. Current user is: ";
        _app.show_user_info(login);
        _current_login = login;
        _current_user_type = user_type;
        _current_password = password;
	};

    void registration() {
        std::string login, password, name, surname;
        std::cout << "\nEnter login: "; 
        std::getline(std::cin >> std::ws, login);
		std::cout << "\nEnter password: ";
        std::getline(std::cin >> std::ws, password);
        std::cout << "\nEnter name: ";
        std::getline(std::cin >> std::ws, name);
        std::cout << "\nEnter surname: ";
        std::getline(std::cin >> std::ws, surname);
        _app.register_client(login, password, name, surname);
    };

    void ShowActions()
    {
		switch (_current_user_type)
		{
        case kClient: {
            DoClientActions();
            return; }
		case kWorker:{
            DoWorkerActions();
			return; }
        case kAdmin:{
			DoAdminActions();
			return; }
		default:
			break;
		}
    }


private:
    void RegisterClient(std::string login, std::string password)
    {
		std::vector<std::string> items = { "Exit", "Yes",  "No", };
		auto choice = Choice("User not found, do you want to register new user?", items);
		switch (choice)
		{
		case 0: throw std::domain_error("User wants to exit.");
		case 1: {
			std::string name, surname;
			std::cout << "\nEnter your name: ";
            std::getline(std::cin >> std::ws, name);
			std::cout << "\nEnter your surname: ";
            std::getline(std::cin >> std::ws, surname);
			_app.register_client(login, password, name, surname);
			return; }
		default: throw std::domain_error("User doesn't want to register.");
			break;
		}

    }

    static int Choice(const std::string &header, const std::vector<std::string>& items) {
        int choice = 0;
        do {
            std::cout << header << std::endl;
            for (int i = 1; i < items.size(); ++i) {
                std::cout << i << ". " << items[i] << std::endl;
			}
            std::cout << "-------------\n";
            std::cout << 0 << ". " << items[0] << std::endl;
            std::cin >> choice;
        } while (choice<0 || choice > items.size() - 1);
        return choice;
    }

    void DoClientActions()
    {
        do {
			std::vector<std::string> items = { "Exit", "View tours",  "View my vouchers", "Change password"};
			auto choice = Choice("Client operations", items);
            switch (choice)
            {
            case 0:
                return;
            case 1: {_app.show_tours();
                std::cout << "Wanna buy a tour?\n\t1. Yes\n\t2. No\n";
                int y_n = 0;
                do {
                    std::cin >> y_n;
                } while (y_n != 1 && y_n != 2);
                if (y_n == 1) {
                    std::cout << "Type in the name of the tour you want to buy:";
                    std::string buy_name;
                    std::getline(std::cin>>std::ws, buy_name);
                    int visitors, id;
                    std::cout << "Type in how many people will be here: ";
                    std::cin >> visitors;
                    id=_app.create_voucher(_current_login, buy_name, visitors);
                    std::cout << "You name have a new voucher with id: `" << id << "`.\n";
                }
                break; }
            case 2: {_app.show_client_vouchers(_current_login);
                break; }
            case 3: {
                std::cout << "Enter new password: ";
                std::string new_password;
                std::getline(std::cin >> std::ws, new_password);
                _app.change_password(_current_login, _current_password, new_password);
                _current_password = new_password;
                break; }

            }
        } while (true);
    }

	void DoWorkerActions() {
		do {
			std::vector<std::string> items = { "Exit", "View tours",  "View certain clients's vouchers", "Change password", "Show all vouchers", "Add Tours" };
			auto choice = Choice("Worker operations", items);
			switch (choice)
			{
			case 0:
				return;
			case 1: {_app.show_tours();
				break; }
			case 2: {std::cout << "Enter client's login: ";
				std::string client_login;
                std::getline(std::cin >> std::ws, client_login);
				_app.show_client_vouchers(client_login);
				break; }
			case 3: {
				std::cout << "Enter new password: ";
				std::string new_password;
                std::getline(std::cin >> std::ws, new_password);
				_app.change_password(_current_login, _current_password, new_password);
				_current_password = new_password;
				break; }
            case 4: {
                _app.show_all_vouchers();
                break;
            }
            case 5: {
                std::cout << "Enter tour name: ";
                std::string tour_name, tour_description;
                std::getline(std::cin >> std::ws, tour_name);
                std::cout << "Enter tour description: ";
                std::getline(std::cin >> std::ws, tour_description);
                std::cout << "Enter tour duration and cost: ";
                int tour_duration, tour_cost;
                    std::cin >> tour_duration>>tour_cost;
                    _app.create_tour(tour_name, tour_description, tour_duration, tour_cost);
            }
			}

		} while (true);
    }

	void DoAdminActions() {
		do {
			std::vector<std::string> items = { "Exit", "View sales", "Add workers" };
			auto choice = Choice("Admin operations", items);
			switch (choice)
			{
			case 0:
				return;
			case 1: {_app.show_sales();
				break; }
			case 2: {std::cout << "Enter worker's login: ";
				std::string w_login, w_password, w_name, w_surname;
				std::getline(std::cin >> std::ws, w_login);
				std::cout << "\nEnter password: ";
				std::getline(std::cin >> std::ws, w_password);
				std::cout << "\nEnter name: ";
				std::getline(std::cin >> std::ws, w_name);
				std::cout << "\nEnter surname: ";
				std::getline(std::cin >> std::ws, w_surname);
				_app.register_worker(w_login, w_password, w_name, w_surname);
                std::cout << "Worker registered successfully\n";
				break; }
			}

		} while (true);
	}

	TourApplication& _app;
	//std::vector<std::string> _names_vector;

	std::string _current_login;
    std::string _current_password;
    UserType _current_user_type = kUndefined;
    


};

