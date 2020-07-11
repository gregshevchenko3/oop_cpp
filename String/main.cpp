#include "String.hpp"
#include <cstdio>

int main() {
	String str1, str2 = 5, str3 = "Hello ", str4 = "World!";

	String str5 = str3 + str4;

	std::cout << str5 << std::endl;
	std::cin >> str1;
	std::cout << str1 << std::endl << str1.size() << std::endl;
	std::cout << "Press any key..." << std::endl;
	getc(stdin);
	return 0;
}