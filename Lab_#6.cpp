#include <iostream>

#define MY_MAX_SIZE 5

class MyException
{
private:
	std::string message = "MyExeption";

public:
	MyException(std::string&& message) : message(message) {}
	const char* what() const noexcept
	{
		return message.c_str();
	}

};

class MySet {
private:
	int _cont[MY_MAX_SIZE];
	int _var;
	int _elem_num;
	int i;
public:
	void num_init() {
		_elem_num = 0;
	}
	//Добавляет элемент, кидает исключение, если уже есть такой элемент или слишком много элементов 
	void my_add(int elem) {
		if (_elem_num == MY_MAX_SIZE) {
			throw MyException("Exception, too many elements in the Set\n");
			return;
		}
		for (i = 0; i < _elem_num; i++) {
			if (elem == _cont[i]) {
				throw MyException("Exception, this element is already in the Set\n");
				return;
			}
		}
		if (_elem_num == 0) {
			_cont[0] = elem;
			_elem_num++;
			return;
		}
		for (i = 0; i < _elem_num; i++) {
			if (elem < _cont[i]) {
				for (int j = _elem_num; j > i; j--) {
					_cont[j] = _cont[j - 1];
					_cont[j - 1] = elem;
				}
				_elem_num++;
				return;
			}
			if (i == _elem_num - 1) {
				_cont[i + 1] = elem;
				_elem_num++;
				return;
			}
		}
	}
	//Выводит все элементы, кидает исключение, если элементов нет
	void my_show() {
		if (_elem_num == 0) {
			throw MyException("Exception, no elements in the Set");
			return;
		}
		std::cout << "Elements are:" << std::endl;
		for (i = 0; i < _elem_num; i++) {
			std::cout << _cont[i] << std::endl;
		}
	}
	//Удаляет элемент, кидает исколючение, если элементов нет 
	void my_delete(int elem) {
		if (_elem_num == 0) {
			throw MyException("Exception, no elements in the Set");
			return;
		}
		_var = my_search(elem);
		for (i = _var; i < _elem_num; i++) {
			_cont[i] = _cont[i + 1];
		}
		_elem_num--;
		return;
	}
	//Находит элемент по значению, кидает исключение если элемента нет
	int my_search(int elem) {
		for (i = 0; i < _elem_num; i++) {
			if (elem == _cont[i]) {
				return i;
			}
		}
		throw MyException("Exception, no such element in the Set");
	}
	void menu()
	{
		int choice = 0;
		do {
			std::cout << std::endl;
			std::cout << "Choose what you wnat:" << std::endl
				<< "1. Write into set" << std::endl
				<< "2. Delete from set" << std::endl
				<< "3. Show set" << std::endl
				<< "4. Search by element" << std::endl
				<< "5. Exit" << std::endl
				<< "Enter: ";
			choice = input();
			std::cout << std::endl;
			switch (choice)
			{
			case 1:
				std::cout << "Enter the new number: ";
				my_add(input());
				break;
			case 2:
				std::cout << "Enter the numberto delete: ";
				my_delete(input());
				break;
			case 3:
				my_show();
				break;
			case 4:
				std::cout << "Enter the searched number: ";
				std::cout<<"The position is "<<my_search(input());
				break;
			case 5:
				break;
			default:
				std::cout << "Incorrect value, try again\n";
				break;
			}
		} while (choice != 5);
	}
	int input() {
		int num;
		if (!(std::cin >> num)) {
			throw MyException("Exception, incorrect input");
		}
		else return num;
	}
	//Функция unexpected
	void my_unexpected_fun() throw (MyException) {
		throw std::domain_error("Should be called unexpected");
	}
};

void new_terminate()
{
	std::cout << " my terminate handler!" << std::endl;
	exit(-1);
}

void my_unexpected()
{
	std::cout << "my unexpected handler" << std::endl;
}


int main()
{
	int i = 0;	
	set_terminate(new_terminate);
	set_unexpected(my_unexpected);
	MySet my_set;
	my_set.num_init();

	try
	{
		my_set.menu();
	}
	catch (const MyException& err)
	{
		std::cout << err.what() << std::endl;
	}
	//my_set.my_delete(999); //Проверка на исключение вне try(...) catch

	return 0;
}
