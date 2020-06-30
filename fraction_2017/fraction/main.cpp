#include <iostream>
#include "fraction.h"

int main() {
	fraction f1 = 3.14, f2 = 2, f3 = 2.7;
	double fl = 1.999;
	fraction f4 = fl;

	/*std::cout << "f1 = " << (const char*)f1 << std::endl;
	std::cout << "f2 = " << (const char*)f2 << std::endl;
	std::cout << "f3 = " << (const char*)f3 << std::endl;*/
	std::cout << "f4 = " << (const char*)f4 << std::endl;

	/*std::cout << "test -f1 = " << (const char*)(-f1) << std::endl;
	
	std::cout << "test f1 + f2 = " << (const char*)(f1 + f2) << std::endl;
	std::cout << "test f1 - f3 = " << (const char*)(f1 - f3) << std::endl;
	std::cout << "test f1 * f2 = " << (const char*)(f1 * f2) << std::endl;
	std::cout << "test f1 / f2 = " << (const char*)(f1 / f2) << std::endl;

	std::cout << std::boolalpha;
	std::cout << "test f1 > f2 = " << (f1 > f2) << std::endl;
	std::cout << "test f1 < f3 = " << (f1 < f3) << std::endl;
	std::cout << "test f1 != f2 = " << (f1 != f2) << std::endl;
	std::cout << "test f1 == f1 = " << (f1 == f1) << std::endl;
	std::cout << "test f1 >= f1 = " << (f1 >= f1) << std::endl;
	std::cout << "test f1 <= f3 = " <<  (f1 <= f3) << std::endl;*/

	return 0;
}