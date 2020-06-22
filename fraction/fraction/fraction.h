#pragma once
#include <limits>
#include <vector>
#include <string>
class fraction
{
	long long m_whole;
	long long m_numerator;
	long long m_denominator;
public:
	static const long long maximum_denominator_allowed = std::numeric_limits<long>::max() - 1;
private:
	void __aproximate_real_number(double fract_part);
	/**
	 * ��� ����� ������� ��� ���� ������������ ��� ���������� ����� (� ����� normalize()), ��� �������� �������
	 * ����������� ��� � double, � ���� �������� ��� � double.
	 */
	//std::vector<long long> __get_simple_factors(long long n);
public:
	fraction(long long numerator = 0, long long denominator = 1, long long whole = 0);
	fraction(long whole);
	fraction(unsigned long whole);
	fraction(int whole);
	fraction(unsigned int whole);
	fraction(short whole);
	fraction(unsigned short whole);
	fraction(char);
	fraction(unsigned char whole);
	fraction(float dec_fraction);
	fraction(double dec_fraction);
	
	/**
	 * ������ � ����� ���� �������, � ������� ���.
	 */
	fraction normalize();

	/**
	 * ����� ���������� ��������
	 */
	fraction operator+();
	fraction operator-();
	fraction operator-() const;
	fraction operator++(int);
	fraction& operator++();
	fraction operator--(int);
	fraction& operator--();

	/** 
	 * ���������� ���� �� ����� ��������� ������ �������, � ���������� ����
	 */
	operator long long() const;
	operator unsigned long long() const;
	operator long() const;
	operator unsigned long() const;
	operator int() const;
	operator unsigned int() const;
	operator short() const;
	operator unsigned short() const;
	operator char() const;
	operator unsigned char() const;
	
	/**
	 * ������������ ����� � ���������� � ��������.
	 */
	operator float() const;
	operator double() const;
	operator long double() const;

	/**
	 * ������� �-�����-������������� ����� � ������ m_whole + m_numerator/m_denumerator
	 */
	operator const char*() const;

	/**
	 * ������ ���������� ��������
	 */
	fraction& operator+=(const fraction& other);
	fraction& operator-=(const fraction& other);
	fraction& operator*=(const fraction& other);
	fraction& operator/=(const fraction& other);
	fraction operator+(const fraction& other);
	fraction operator-(const fraction& other);
	fraction operator*(const fraction& other);
	fraction operator/(const fraction& other);
	/**
	 * ������ �������� ���������
	 */
	bool operator==(const fraction& other);
	bool operator!=(const fraction& other);
	bool operator>(const fraction& other);
	bool operator<(const fraction& other);
	bool operator>=(const fraction& other);
	bool operator<=(const fraction& other);
};

