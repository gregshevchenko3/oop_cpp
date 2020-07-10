#include "Fraction.hpp"

int Fraction::get_integer()const
{
	return this->integer;
}
int Fraction::get_numerator()const
{
	return this->numerator;
}
int Fraction::get_denominator()const
{
	return this->denominator;
}
void Fraction::set_integer(int integer)
{
	this->integer = integer;
}
void Fraction::set_numerator(int numerator)
{
	this->numerator = numerator;
}
void Fraction::set_denominator(int denominator)
{
	if (denominator == 0)denominator = 1;
	this->denominator = denominator;
}

//			Constructors:
Fraction::Fraction() : integer(0), numerator(0), denominator(1)
{}
Fraction::Fraction(int integer) : numerator(0), denominator(1)
{
	this->integer = integer;
}
Fraction::Fraction(int numerator, int denominator)
{
	this->integer = 0;
	this->numerator = numerator;
	this->set_denominator(denominator);
}
Fraction::Fraction(int integer, int numerator, int denominator)
{
	set_integer(integer);
	set_numerator(numerator);
	set_denominator(denominator);
}
Fraction::Fraction(float dec_fraction)
{
	/*bool sign = dec_fraction < 0;
	float whole;
	float fract = modf(dec_fraction, &whole);
	m_whole = whole;
	__aproximate_real_number((sign) ? -fract : fract);
	if (sign) m_numerator = -m_numerator;*/
	integer = dec_fraction;
	dec_fraction -= integer;
	numerator = dec_fraction * 10000000;
	denominator = 10000000;
	reduce();
	if (!integer) {
		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		}
	}
	else
	{
		if (denominator < 0)
			denominator = -denominator;
	}
}
Fraction::Fraction(double dec_fraction)
{
	/*bool sign = dec_fraction < 0;
	double whole;
	double fract = modf(dec_fraction, &whole);
	m_whole = whole;
	__aproximate_real_number((sign) ? -fract : fract);
	if (sign) m_numerator = -m_numerator;*/
	integer = dec_fraction;
	dec_fraction -= integer;
	numerator = dec_fraction * 100000000;
	denominator = 100000000;
	reduce();
	if (!integer) {
		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		}
	} 
	else
	{
		if (denominator < 0) 
			denominator = -denominator;
	}
}
/* -2(1/2)*/
//			Methods:
Fraction& Fraction::to_proper()
{
	integer = (integer > 0)?integer + numerator / denominator : ((integer)? integer - numerator / denominator : numerator / denominator);
	numerator %= denominator;
	return *this;
}
Fraction& Fraction::to_improper()
{
	numerator = (integer > 0)? numerator + integer * denominator : ((integer) ? integer - numerator / denominator : numerator);
	integer = 0;
	return *this;
}
Fraction& Fraction::reduce()
{
	int lcf = largest_common_factor(numerator, denominator);
	if (lcf) {
		numerator /= lcf;
		denominator /= lcf;
	}
	return *this;
}
void Fraction::print() const
{
	std::string tmp = *this;
	std::cout << tmp << std::endl;
}

int Fraction::largest_common_factor(int n, int d)
{
	if (!n) return 0;
	int reminder = 0, result = d;
	do {
		reminder = result % n;
		result = n;
		n = reminder;
	} while (reminder);
	return (result != d) ? result : 0;
}
Fraction& Fraction::operator_finalize()
{
	to_proper();
	reduce();
	return* this;
}
void Fraction::operator_begin(Fraction& other)
{
	to_improper();
	reduce();
	other.to_improper();
	other.reduce();
}
Fraction::operator bool()
{
	return this->integer * this->denominator + numerator;
}
Fraction::operator int()
{
	return this->integer;
}
Fraction::operator float()
{
	return (float)numerator / denominator + integer;
}
Fraction::operator double()
{
	return (double)numerator / denominator + integer;
}

Fraction::operator std::string() const
{
	std::stringstream ss;
	if (integer)
		ss << integer;
	if (numerator)
	{
		if (integer)
			ss << "(";
		ss << numerator << "/" << denominator;
		if (integer)
			ss << ")";
	}
	else if (integer == 0) ss << 0;
	return ss.str();
}

Fraction& Fraction::operator+=(const Fraction& other)
{
	// TODO: insert return statement here
	Fraction othr = other;
	operator_begin(othr);
	int den = this->denominator;
	this->denominator *= othr.denominator;
	this->numerator = this->numerator * othr.denominator + othr.numerator * den;
	return operator_finalize();
}
Fraction& Fraction::operator-=(const Fraction& other)
{
	Fraction othr = other;	
	operator_begin(othr);
	int den = this->denominator;
	this->denominator *= othr.denominator;
	this->numerator = this->numerator * othr.denominator - othr.numerator * den;
	return operator_finalize();
}
Fraction& Fraction::operator*=(const Fraction& other)
{
	Fraction othr = other;
	operator_begin(othr);
	this->numerator *= othr.numerator;
	this->denominator *= othr.denominator;
	return operator_finalize();
}
Fraction& Fraction::operator/=(const Fraction& other)
{
	// TODO: insert return statement here
	Fraction othr = other;
	if (other == 0) throw std::logic_error("division by zero");
	operator_begin(othr);
	this->numerator *= othr.denominator;
	this->denominator *=  othr.numerator;
	return operator_finalize();
}
Fraction& Fraction::operator++()
{
	// TODO: insert return statement here
	return *this += 1;
}
Fraction Fraction::operator-()
{
	if (integer) integer = -integer;
	else
		if (numerator) numerator = -numerator;
	return *this;
}
Fraction& Fraction::operator--()
{
	// TODO: insert return statement here
	return *this -= 1;
}
Fraction Fraction::operator++(int)
{
	Fraction result = *this;
	*this += 1;
	return result;
}
Fraction Fraction::operator--(int)
{
	Fraction result = *this;
	*this -= 1;
	return result;

}
Fraction operator+(Fraction left, const Fraction& right)
{
	return left += right;
}
Fraction operator-(Fraction left, const Fraction& right)
{
	return left-=right;
}
Fraction operator*(Fraction left, const Fraction& right)
{
	return left *= right;
}
Fraction operator/(Fraction left, const Fraction& right)
{
	return left /= right;
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(right == left);
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	left -= right;
	double result = left;
	return (result > 0);
}
bool operator<(const Fraction& left, const Fraction& right)
{
	return !(left >= right);
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return left > right || left == right;
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right) || left == right;
}
bool operator==(const Fraction& left, const Fraction& right)
{
	return left.get_integer() == right.get_integer() &&
		left.get_numerator() == right.get_numerator() &&
		left.get_denominator() == right.get_denominator();
}

