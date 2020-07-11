// String.cpp : Defines the entry point for the application.
//

#include "String.hpp"
#include <cstring>

String::String() : m_str(new char[80] {0}), m_size(80)
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
char& String::operator[](int position) const
{
	return m_str[position];
}
char& String::operator[](int position)
{
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

std::istream& operator>>(std::istream& in, String& str)
{
	auto last_non_zero_index = 0;
	for (auto i{0}; i < str.size(); i++)
		if (str[i]) last_non_zero_index++;

	while ('\n' != in.peek()) {
		if (last_non_zero_index < str.size())
			str[last_non_zero_index++] = in.get();
		else {
			last_non_zero_index++;
			char ch[2] = { in.get(), 0, };
			str += ch;
		}
	} 
	if (last_non_zero_index < str.size()) {
		char* tmp = new char[last_non_zero_index];
		std::copy(str.m_str, str.m_str + last_non_zero_index, tmp);
		delete[] str.m_str;
		str.m_str = tmp;
		str.m_size = last_non_zero_index;
	}
	return in;
}

String operator+(String left, const String& right)
{
	return left+=right;
}
