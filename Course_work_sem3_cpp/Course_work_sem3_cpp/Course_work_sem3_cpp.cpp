#include <iostream>
#include <vector>
#include "TourApplication.h"
#include "Serializable.h"
#include "User.h"
#include <chrono>
#include "Menu.h"
#include <fstream>

//Ќаписать курсовую по теме туристическое агенство
// ошибки в проверке парол€, выводе меню действий, регистрации клиента
//  ласс параметров
class Properties 
{
public:
    void define_password(int a) {
        password = a;
    }
protected:
    int password;
};

const char* storage_name = "Tour_objects_file.txt";

int main()
{
	try
	{
		TourApplication app;
		std::cout << "Tour application starting..." << std::endl;
		{
			std::ifstream fin(storage_name);
			if (!fin.is_open()) {
				//std::cout << "Tour application data is initialized." << std::endl;
				//app.register_client("Login1", "Loginpass1", "Jack", "Sparrow");
				//app.register_worker("Login2", "Loginpass2", "Black", "Beard");
				//app.register_worker("Admin", "AdminPass", "Cool", "Administrator");
				//app.create_tour("Maldives", "Resort on a beach", 5, 1500);
				//app.create_tour("Dubai", "Nice atmosphere", 7, 1000);
			}
			else {
				app.Load(fin);
				std::cout << "Tour application data is loaded." << std::endl;
			}
		}
		Menu menu(app);
		menu.Login();
		menu.ShowActions();
		{
			std::ofstream fout;
			fout.open(storage_name);
			if (!fout.is_open()) {
				throw std::domain_error("File opening error");
			}
			app.Save(fout);
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		std::cerr << "Application terminated." << std::endl;
	}
    return 0;
}

