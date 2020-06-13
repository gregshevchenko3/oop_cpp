#include <iostream>

class point {
	double x, y;
public:
	double get_x() const
	{
		return x;
	}
	double get_y() const
	{
		return y;
	}
	void set_x(double x) 
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}
	
	point(double x = double(), double y = double())
	{
		this->x = x;
		this->y = y;
		std::cout << "DefaultConstructor:\t" << this << std::endl;
	}
	~point()
	{
		std::cout << "Destructor:\t" << this << std::endl;

	}

	void print() const
	{
		std::cout << x << "\t" << y << std::endl;
	}
};

void main() {
	using namespace std;
#ifdef _STRUCTURES_
	struct point A;
	A.x = 2.;
	A.y = 3.;
	cout << A.x << "\t" << A.y << endl;

	struct point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
	cout << (*pA).x << "\t" << (*pA).y << endl;
#endif
	point A;
	cout << A.get_x() << '\t' << A.get_y() << endl;
	point B(5, 4);
	B.print();

}