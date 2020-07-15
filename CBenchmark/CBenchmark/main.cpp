#include "CBenchmark.hpp"
#include <iostream>

BENCHMARKING("E:/test2.json");

void f1()
{
	//Timer t1(__func__);
	TRACE
	std::cout << "F1" << std::endl;
}

int main()
{
	//Timer t2(__func__);
	TRACE
	f1();
	std::cout << "Hello world" << std::endl;
}