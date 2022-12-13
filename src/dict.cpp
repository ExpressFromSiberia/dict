#include <iostream>

#include "dict.h"

int main() {

	m_dict<int, int> test_dict;
	test_dict.set(1, 6);
	bool check = test_dict.is_set(1);
	try
	{
		m_dict<std::string, int> test_dict;
		std::string a = "hello";
		std::cout << &a << std::endl;
		int tmp = test_dict.get(a);
	}
	catch (m_exception<std::string>& ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << "Error key = " << ex.get_key() << std::endl;
	}

	return 0;
}