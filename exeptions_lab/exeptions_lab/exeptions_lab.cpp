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
	void my_add(int elem) {
		
		if (elem == 0) {
			throw MyException("Exception, the element can't be 0\n");
			return;
		}
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
				_cont[i+1] = elem;
				_elem_num++;
				return;
			}
		}
	}
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
	void my_delete(int elem) {
		if (_elem_num == 0) {
			throw MyException("Exception, no elements in the Set");
			return;
		}
		_var = my_search(elem);
		for (i = _var; i < _elem_num; i++) {
				_cont[i] = _cont[i+1];
			}
			_elem_num--;
			return;
	}
	void my_unexpected_fun() throw (MyException){
		throw std::domain_error("Should be called unexpected");
	}

	int my_search(int elem) {
		for (i = 0; i < _elem_num; i++) {
			if (elem == _cont[i]) {
				return i;
			}
		}
		throw MyException("Exception, no such element in the Set");
	}
};

void new_terminate()
{
	std::cout << " my terminate handler!"<< std::endl;
	exit(-1);
}

void my_unexpected()
{
	std::cout << "my_unexpected handler" << std::endl;
}

int main()
{
	set_terminate(new_terminate);
	set_unexpected(my_unexpected);
	MySet my_set;
	int var = 0;
	try
	{
		//for (int i = 0; i < MY_MAX_SIZE; i++) {
		//	std::cin >> var;
		//	my_set.my_add(var);
		//	std::cout << "\nAdded new element\n";
		//}
	my_set.num_init();
	my_set.my_add(2);
	//my_set.my_add(2);
	my_set.my_add(10);
	my_set.my_add(5);
	my_set.my_add(1);
	my_set.my_add(3);
	//my_set.my_add(10);
	my_set.my_show();
	//my_set.my_delete(7);
	my_set.my_delete(10);
	my_set.my_show();
	my_set.my_add(10);
	my_set.my_show();
	my_set.my_unexpected_fun();
	std::cout << "No exceptions within try-catch\n";
	}
	catch (const MyException& err)
	{
		std::cout << err.what() << std::endl;
	}
	/*my_set.my_delete(64);*/

	return 0;
}