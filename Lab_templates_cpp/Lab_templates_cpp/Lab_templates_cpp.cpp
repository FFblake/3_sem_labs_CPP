#include <iostream>

template <typename type>
int binar_search(type* arr, type elem, int l, int h)
{
	if (h >= l)
	{
		int mid = l + (h - l) / 2;
		if (arr[mid] == elem)
			return mid;
		if (arr[mid] > elem)
			return binar_search(arr, elem, l, mid - 1);
		else
		return binar_search(arr, elem, mid + 1, h);
	}
	std::cout << "\nThere is no such element\n";
	return -1;
}

template<typename type>
void sort_f(type* arr, int size) {
	type var;
	for (int i = 0; i < size; i++) {
		for (int j = size - 1; j > 0; j--) {
			if (arr[j] < arr[j - 1]) {
				var = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = var;
			}
		}
	}
}

int main()
{
	int size = 10, check =0;
	int* int_arr = new int[size];
	std::cout << "Enter 10 integer numbers:\n";
	for (int i = 0; i < size; i++) {
		if (!(std::cin >> int_arr[i])) {
			std::cout << "\nWrong input";
		}
	}
	sort_f(int_arr, size);
	std::cout << "Enter the number, that you want to find\n";
	int num_1;
	if (!(std::cin >> num_1)) {
		std::cout << "\nWrong input";
	}
	//for (int i = 0; i < size; i++) {
	//	if (num_1 == int_arr[i]) {
	//		check = 1;
	//	}
	//}
	//if (check == 1) check = 0;
	//else return 0;
	std::cout << '\n' << "The position of your chosen element is: " << binar_search(int_arr, num_1, 0, size - 1) << '\n';
	delete[] int_arr;



	float* float_arr = new float[size];
	std::cout << "Enter 10 float numbers:\n";
	for (int i = 0; i < 10; i++) {
		if (!(std::cin >> float_arr[i])) {
			std::cout << "\nWrong input";
		}
	}
	sort_f(float_arr, size);
	std::cout << "Enter the number, that you want to find\n";
	float num_2;
	if (!(std::cin >> num_2)) {
		std::cout << "\nWrong input";
	}
	//for (int i = 0; i < size; i++) {
	//	if (num_2 == float_arr[i]) {
	//		check = 1;
	//	}
	//}
	//if (check == 1) check = 0;
	//else return 0;
	std::cout << '\n' << "The position of your chosen element is: " << binar_search(float_arr, num_2, 0, size - 1)<< '\n';
	delete[] float_arr;



	char char_arr[10];
	std::cout << "Enter 10 symbols:\n";
	for (int i = 0; i < size; i++) {
		if (!(std::cin >> char_arr[i])) {
			std::cout << "\nWrong input";
		}
	}
	std::cout << "Enter the number, that you want to find\n";
	char letter;
	if (!(std::cin >> letter)) {
		std::cout << "\nWrong input";
	}
	//for (int i = 0; i < size; i++) {
	//	if (letter == char_arr[i]) {
	//		check = 1;
	//	}
	//}
	//if (check == 1) check = 0;
	//else return 0;
	sort_f(char_arr, 10);
	std::cout << "The position of your chosen element is: "<<binar_search(char_arr, letter, 0, 9);
}