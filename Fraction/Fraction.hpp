#pragma once

#include <iostream>
#include <sstream>

class Fraction
{
	long long integer;	//целая часть
	long long numerator;	//числитель
	long long denominator;//знаменатель
public:
	int get_integer()const;
	int get_numerator()const;
	int get_denominator()const;
	void set_integer(int integer);
	void set_numerator(int numerator);
	void set_denominator(int denominator);


	Fraction(); 
	Fraction(int integer);
	Fraction(int numerator, int denominator);
	Fraction(int integer, int numerator, int denominator);
	Fraction(float dec_fraction);
	Fraction(double dec_fraction);
	// Якщо конструктор копіювання та деструктор реаліізовуються неявно, то для чого їх реалізовати явно.

	Fraction& to_proper();
	Fraction& to_improper();
	Fraction& reduce();
	void print()const;

private:
	int largest_common_factor(int n, int d);
	Fraction& operator_finalize();
	void operator_begin(Fraction& other);

public:
	operator bool();
	operator int();
	operator float();
	operator double();
	operator std::string() const;
	
	Fraction& operator+=(const Fraction& other);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);

	Fraction& operator++();
	Fraction operator-();
	Fraction& operator--();
	Fraction operator++(int);
	Fraction operator--(int);
};

Fraction operator+(Fraction left, const Fraction& right);
Fraction operator-(Fraction left, const Fraction& right);
Fraction operator*(Fraction left, const Fraction& right);
Fraction operator/(Fraction left, const Fraction& right);

bool operator==(const Fraction& left, const Fraction& right);
bool operator!=(const Fraction& left, const Fraction& right);
bool operator>(Fraction left, Fraction right);
bool operator<(const Fraction& left, const Fraction& right);
bool operator>=(const Fraction& left, const Fraction& right);
bool operator<=(const Fraction& left, const Fraction& right);
