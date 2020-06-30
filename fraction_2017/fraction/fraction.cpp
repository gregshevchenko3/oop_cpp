#include "fraction.h"
#include <sstream>
#include <cmath>
#include <cstring>
#include <iostream>

/************************************************************************************************ CONSTRUCTORS */
fraction::fraction(long long numerator, long long denominator, long long whole): m_whole(whole), m_numerator(numerator), m_denominator(denominator)
{}
//fraction::fraction(long whole) : m_whole(whole), m_numerator(0), m_denominator(1)
//{}
//fraction::fraction(unsigned long whole) : m_whole(whole), m_numerator(0), m_denominator(1)
//{}
//fraction::fraction(int whole) : m_whole(whole), m_numerator(0), m_denominator(1)
//{}
//fraction::fraction(unsigned int whole) : m_whole(whole), m_numerator(0), m_denominator(1)
//{}
//fraction::fraction(short whole) : m_whole(whole), m_numerator(0), m_denominator(1)
//{}
//fraction::fraction(unsigned short whole) : m_whole(whole), m_numerator(0), m_denominator(1)
//{}
//fraction::fraction(char whole) : m_whole(whole), m_numerator(0), m_denominator(1)
//{}
//fraction::fraction(unsigned char whole) : m_whole(whole), m_numerator(0), m_denominator(1)
//{}
fraction::fraction(float dec_fraction)
{
	bool sign = dec_fraction < 0;
	float whole;
	float fract = modf(dec_fraction, &whole);
	m_whole = whole;
	__aproximate_real_number((sign) ? -fract : fract);
	if (sign) m_numerator = -m_numerator;
}

fraction::fraction(double dec_fraction)
{
	bool sign = dec_fraction < 0;
	double whole;
	double fract = modf(dec_fraction, &whole);
	m_whole = whole;
	__aproximate_real_number((sign)?-fract:fract);
	if (sign) m_numerator = -m_numerator;
}

/************************************************************************************************* METHODS */
fraction fraction::normalize()
{
	/*fraction result = *this;
	if (result.m_numerator >= result.m_denominator) 
	{
		result.m_whole += result.m_numerator / result.m_denominator;
		result.m_numerator %= result.m_denominator;
	}
	auto numerator_factors = __get_simple_factors(result.m_numerator), denominator_factors = __get_simple_factors(result.m_denominator);
	if (numerator_factors.size() > 1 && denominator_factors.size() > 1)
	{
		for (auto it = numerator_factors.begin(); it < numerator_factors.end(); it++) 
		{
			auto denom_it = denominator_factors.end();
			if ((denom_it = std::find(denominator_factors.begin(), denominator_factors.end(), *it)) != denominator_factors.end()) 
			{
				result.m_numerator /= *it;
				result.m_denominator /= *it;
				denominator_factors.erase(denom_it);
			}
		}
	}
	return result;*/
	double result = *this;
	return result;
}
void fraction::__aproximate_real_number(double fract_part)
{
	// Взято з: hhtps://www.ics.uci.edu/~eppstein/numth/frap.c
	if (fract_part < 1.) {
		double startx = fract_part;
		long long m[2][2], ai;

		m[0][0] = m[1][1] = 1;
		m[0][1] = m[1][0] = 0;

		while (m[1][0] * (ai = (long long)fract_part) + m[1][1] <= fraction::maximum_denominator_allowed)
		{
			long long t;
			t = m[0][0] * ai + m[0][1];
			m[0][1] = m[0][0];
			m[0][0] = t;
			t = m[1][0] * ai + m[1][1];
			m[1][1] = m[1][0];
			m[1][0] = t;
			if (fract_part == (double)ai) break;
			fract_part = 1 / (fract_part - (double)ai);
			if (fract_part > (double)std::numeric_limits<long long>::max()) break;
		}
		m_numerator = m[0][0];
		m_denominator = m[1][0];
	}
}
// wheel factorization
//std::vector<long long> fraction::__get_simple_factors(long long n)
//{
//	using vT = std::vector<long long>;
//	vT factors;
//	if (!(n % 2)) {
//		factors.push_back(2);
//		n /= 2;
//	}
//	if (!(n % 3)){
//		factors.push_back(3);
//		n /= 3;
//	}
//	if (!(n % 5)) {
//		factors.push_back(5);
//		n /= 5;;
//	}
//	long long k = 7; 
//	auto i = 0;
//	// Масив зміщень по Wheel factorization 
//	long long inc[] = { 4, 2, 4, 2, 4, 6, 2, 6 };
//	while (k*k <= n) 
//	{
//		if (!(n%k)) {
//			factors.push_back(k);
//			n /= k;
//		}
//		else {
//			k += inc[i];
//			if (i < 8) 
//				i++;
//			else i = 0;
//		}
//		
//	}
//	factors.push_back(n);
//	return factors;
//}
/************************************************************************************************* UNARY OPERATORS */
fraction fraction::operator+()
{
	return fraction(*this);
}
fraction fraction::operator-()
{
	fraction result = *this;
	result.m_numerator = -result.m_numerator;
	result.m_whole = -result.m_whole;
	return result;
}
fraction fraction::operator-() const 
{
	fraction result = *this;
	result.m_numerator = -result.m_numerator;
	result.m_whole = -result.m_whole;
	return result;
}
//post increment
fraction fraction::operator++(int)
{
	fraction result(*this);
	this->operator+=(fraction(1));
	return result;
}
//pre increment
fraction& fraction::operator++()
{
	this->operator+=(fraction(1));
	return *this;
}
// post decrement
fraction fraction::operator--(int)
{
	fraction result(*this);
	this->operator-=(fraction(1));
	return result;
}
// pre-decrement
fraction & fraction::operator--()
{
	this->operator-=(fraction(1));
	return *this;
}

/************************************************************************************************* TYPE-CAST OPERATORS */
fraction::operator long long() const
{
	fraction tmp(*this);
	tmp = tmp.normalize();
	return tmp.m_whole;
}
fraction::operator unsigned long long() const
{
	fraction tmp(*this);
	tmp = tmp.normalize();
	return tmp.m_whole;
}
fraction::operator long() const
{
	return (long long)(*this);
}
fraction::operator unsigned long() const
{
	return (unsigned long long)(*this);
}
fraction::operator int() const
{
	return (long long)(*this);
}
fraction::operator unsigned int() const
{
	return (unsigned long long)(*this);
}
fraction::operator short() const
{
	return (long long)(*this);
}
fraction::operator unsigned short() const
{
	return (unsigned long long)(*this);
}
fraction::operator char() const
{
	return (long long)(*this);
}
fraction::operator unsigned char() const
{
	return (unsigned long long)(*this);
}
fraction::operator float() const
{
	float result = m_whole * m_denominator + m_numerator;
	result /= m_denominator;
	return result;
}
fraction::operator double() const
{
	double result = m_whole * m_denominator + m_numerator;
	result /= m_denominator;
	return result;
}
fraction::operator long double() const
{
	long double result = m_whole * m_denominator + m_numerator;
	result /= m_denominator;
	return result;
}
fraction::operator const char*() const {
	std::stringstream ss;
	if (m_whole)
	{
		if (!m_numerator)
			ss << m_whole;
		else if ((m_whole < 0 && m_numerator < 0))
		{
			ss << "-(" << -m_whole << " + " << -m_numerator << "/" << m_denominator << ")";
		}
		else {
			ss << m_whole << " + " << m_numerator << "/" << m_denominator;
		} 
	}
	else {
		if (!m_numerator)
			ss << 0;
		else 
		{
			ss <<  -m_numerator << "/" << m_denominator;
		}
	}
	char* result = new char[ss.str().length() + 1];
	strcpy(result, ss.str().c_str());
	return result;
}

/************************************************************************************************** ASSIGNMENT OPERATORS */
fraction& fraction::operator+=(const fraction & other)
{
	double a = *this;
	a += (double)other;
	this->operator=(a);
	return *this;
}
fraction & fraction::operator-=(const fraction & other)
{
	this->operator+=(-other);
	return *this;
}
fraction & fraction::operator*=(const fraction & other)
{
	double a = *this;
	a *= (double)other;
	this->operator=(a);
	return *this;
}
fraction & fraction::operator/=(const fraction & other)
{
	double a = *this;
	a /= (double)other;
	this->operator=(a);
	return *this;
}

/************************************************************************************************** ARITHMETIC OPERATORS */
fraction fraction::operator+(const fraction & other)
{
	fraction tmp = *this;
	tmp += other;
	return tmp;
}
fraction fraction::operator-(const fraction & other)
{
	fraction tmp = *this;
	tmp -= other;
	return tmp;
}
fraction fraction::operator*(const fraction & other)
{
	fraction tmp = *this;
	tmp *= other;
	return tmp;
}
fraction fraction::operator/(const fraction & other)
{
	fraction tmp = *this;
	tmp /= other;
	return tmp;
}

/************************************************************************************************** COMPARISON OPERATORS */
bool fraction::operator==(const fraction & other)
{
	double a = *this, b = other;
	return a == b;
}
bool fraction::operator!=(const fraction & other)
{
	return !(*this == other);
}
bool fraction::operator>(const fraction & other)
{
	double a = *this, b = other;
	return a > b;
}
bool fraction::operator<(const fraction & other)
{
	return !(*this > other) && *this != other;
}
bool fraction::operator>=(const fraction & other)
{
	return !(*this < other);
}
bool fraction::operator<=(const fraction & other)
{
	return !(*this > other);
}
