#include "Fraction.hpp"
#include <clocale>

using namespace std;

void main()
{
	std::setlocale(LC_ALL, "uk_UA");
	Fraction A = 2, B = 2.7f, C = 3.14;

	/*std::cout << "Тест для A++, ++A, +=" << std::endl;
	(A++).print(); 
	A.print();
	(++A).print();

	std::cout << "Тест для A--, --A, -=" << std::endl;
	(B--).print();
	B.print();
	(--B).print();*/
	(--B).print();

	std::cout << (std::string)A << " + " << (std::string)B << " = " << (std::string)(A + B) << std::endl;
	std::cout << (std::string)A << " - " << (std::string)B << " = " << (std::string)(A - B) << std::endl;
	std::cout << (std::string)A << " * " << (std::string)B << " = " << (std::string)(A * B) << std::endl;
	std::cout << (std::string)A << " / " << (std::string)B << " = " << (std::string)(A / B) << std::endl;
	std::cout << (std::string)Fraction(-0.3) << " / " << (std::string)Fraction(-0.3) << " = " << (std::string)(Fraction(-0.3) / Fraction(-0.3)) << std::endl;
	std::cout << (std::string)Fraction(0.3) << " / " << (std::string)Fraction(-0.3) << " = " << (std::string)(Fraction(0.3) / Fraction(-0.3)) << std::endl;
	std::cout << (std::string)Fraction(-0.3) << " * " << (std::string)Fraction(-0.3) << " = " << (std::string)(Fraction(-0.3) / Fraction(-0.3)) << std::endl;
	std::cout << (std::string)Fraction(0.3) << " * " << (std::string)Fraction(-0.3) << " = " << (std::string)(Fraction(0.3) / Fraction(-0.3)) << std::endl;

	std::cout << "(double)3(7/50) = " << (double)C << std::endl;

	std::cout << std::boolalpha;
	std::cout << (A > B) << std::endl;
	std::cout << (C < A) << std::endl;
	std::cout << (C != A) << std::endl;
	std::cout << (A == A) << std::endl;
	std::cout << (B >= A) << std::endl;
	std::cout << (A <= A) << std::endl;
}