// String.cpp : Defines the entry point for the application.
//

#include "String.hpp"
#include <cstring>

String::String() : m_str(new char[80]), m_size(80)
{}
String::String(int size) : m_str(new char[size]), m_size(size)
{}
String::String(const char* c_str) : m_str(new char[strlen(c_str)]), m_size(strlen(c_str))
{
	std::copy(c_str, c_str + m_size, m_str);
}
String::String(const String& other) : m_str(new char [other.m_size]), m_size(other.m_size)
{
	std::copy(other.m_str, other.m_str + other.m_size, m_str);
}
String::~String()
{
	if (m_str) delete[] m_str;
	if (m_size) m_size = 0;
}
size_t String::size() const
{
	return m_size;
}
char String::operator[](int position) const
{
	if (position >= m_size) return 0;
	return m_str[position];
}
char String::operator[](int position)
{
	if (position >= m_size) return 0;
	return m_str[position];
}
//String& String::operator=(const String& other)
//{
//	if (this == &other) return *this; // fix self-assignment;
//	m_size = other.m_size;
//	m_str = new char[m_size];
//	std::copy(other.m_str, other.m_str + m_size, m_str);
//	return *this;
//}
String& String::operator+=(const String& other)
{
	// TODO: insert return statement here
	char* tmp = m_str;
	m_str = new char[m_size + other.m_size];
	std::copy(tmp, tmp + m_size, m_str);
	std::copy(other.m_str, other.m_str + other.m_size, m_str + m_size);
	m_size += other.m_size;
	delete[] tmp;
	return *this;
}
std::ostream& operator<<(std::ostream& out, const String str)
{
	// TODO: insert return statement here
	int sz = str.size();
	for (int i = 0; i < sz; i++) out << str[i];
	return out;
}

String operator+(String left, const String& right)
{
	return left+=right;
}
