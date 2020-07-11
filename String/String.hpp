// String.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

class String 
{
	char* m_str;
	size_t m_size;
public:
	String();
	String(int size);
	String(const char* c_str);
	String(const String& other);
	~String();

	// Getters
	size_t size() const;
	char& operator[](int position) const;
	// Getter & setter
	char& operator[](int position);

	//String& operator=(const String& other);
	String& operator+=(const String& other);
	friend std::istream& operator>>(std::istream& in, String& str);

};

std::ostream& operator<<(std::ostream& out, const String str);
std::istream& operator>>(std::istream& in, String& str);
String operator+(String left, const String& right);

// TODO: Reference additional headers your program requires here.
