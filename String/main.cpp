#include "String.hpp"

int main() {
	String str1, str2 = 5, str3 = "Hello ", str4 = "World!";

	String str5 = str3 + str4;

	std::cout << str5 << std::endl;
	return 0;
}