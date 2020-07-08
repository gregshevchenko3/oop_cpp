// Matrix.cpp : Defines the entry point for the application.
//

#include "Matrix.h"
#include <iomanip> // for std::setw()

Matrix::Matrix():m_rows(0), m_columns(0), m_matrix(nullptr) 
{
	std::cout << "Constructor empty matrix " << this << std::endl;
}
Matrix::Matrix(size_t rows, size_t columns) : m_rows(rows), m_columns(columns), m_matrix(new double[m_rows * m_columns]{ 0 }) 
{
	std::cout << "Constructor zero matrix " << this << std::endl;

}
Matrix::Matrix(double** arr2d, size_t rows, size_t cols) : Matrix(rows, cols)
{
	std::cout << "Constructor from dynamic array " << this << std::endl;
	for (int i = 0; i < m_rows; i++)
	{
		const double* row_begin = arr2d[i];
		std::copy(row_begin, row_begin + m_columns, m_matrix + i*m_rows);
	}
}
/*
 * Зроблено за прикладом, що знаходиться тут:
 * Наскільки це ефективно з точки зору швидкості виконання коду - не знаю.
 * В іграх та робототехніці точно не використати.
 * https ://en.cppreference.com/w/cpp/utility/initializer_list
 */
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list)
{
	std::cout << "Constructor from initializer list " << this << std::endl;

	auto row_it = list.begin();
	auto end_it = list.end();
	size_t max_length = row_it->size();
	while (row_it != end_it) {
		if (row_it->size() > max_length)
			max_length = row_it->size();
		row_it++;
	}
	row_it = list.begin();

	m_rows = list.size();
	m_columns = max_length;
	if (!m_rows || !m_columns)
	{
		m_rows = m_columns = 0;
		m_matrix = nullptr;
	}
	else
	{
		m_matrix = new double[m_rows * m_columns];

		for (auto i = 0; i < m_rows; i++, row_it++) {
			auto col_it = row_it->begin();
			auto col_end = row_it->end();

			for (auto j = 0; j < m_columns; j++, col_it++) {
				*(m_matrix + i * m_columns + j) = (col_it < col_end) ? *col_it : 0;
			}
		}
	}
}
Matrix::Matrix(size_t rows, size_t columns, std::function<double(size_t row, size_t column)> expr) : m_rows(rows), m_columns(columns), m_matrix(new double[m_rows * m_columns])
{
	std::cout << "Constructor with generator  " << this << std::endl;

	for (auto i{ 0 }; i < rows; i++)
	{
		for (auto j{ 0 }; j < m_columns; j++)
			*(m_matrix + i * m_rows + j) = expr(i, j);
	};
}
Matrix::Matrix(const Matrix& other) 
{
	std::cout << "Copy Constructor " << this << std::endl;

	if (other.is_empty()) {
		m_rows = m_columns = 0;
		m_matrix = nullptr;
	}
	else {
		m_rows = other.m_rows;
		m_columns = other.m_columns;
		m_matrix = new double[m_rows * m_columns];
		const double* row_begin = other.m_matrix;
		std::copy(row_begin, row_begin + m_columns * m_rows, m_matrix);
	}
};
Matrix::~Matrix()
{
	std::cout << "destructor " << this << std::endl;
	if (m_matrix) {
		delete[] m_matrix;
		m_matrix = nullptr;
	}
}
inline void Matrix::__delete_m_matrix()
{
	if (m_matrix) {
		delete[] m_matrix;
		m_matrix = nullptr;
	}
}
Matrix Matrix::transpose()
{
	if (is_empty()) return *this;
	return Matrix(m_columns, m_rows, [this](size_t r, size_t c) {
		return *(m_matrix + c * m_columns + r);
	});
}
Matrix Matrix::inverse()
{
	if (is_empty()) return *this;
	if (m_rows != m_columns) return Matrix();
	double determinant = this->determinant();
	if (!determinant)  return Matrix();
	Matrix adjugate = Matrix(m_rows, m_columns, [this](size_t i, size_t j) {
		return cofactor(i, j);
		}).transpose();
	return adjugate *= (1 / determinant);
}
double Matrix::cofactor(size_t row, size_t column)
{
	return ((row + column) & 1)?-first_minor(row, column):first_minor(row, column);
}
double Matrix::first_minor(size_t row, size_t column)
{
	if (is_empty()) return 0;
	if (m_rows != m_columns) return INFINITY;
	
	Matrix result(m_rows - 1, m_columns - 1);
	for (auto i = 0, j = 0; i < m_rows * m_columns; i++) 
	{
		if (i < row * m_columns || i >= (row + 1) * m_columns)
		{
			if (i % m_columns != column) 
				result.m_matrix[j++] = m_matrix[i];
		}
	}
	return result.determinant();
}
double Matrix::determinant()
{
	double result = 0;
	if (m_rows != m_columns) return INFINITY;
	if (is_empty()) return 0;
	if (m_rows == 1) return m_matrix[0];
	if (m_rows == 2) {
		result = m_matrix[0] * m_matrix[3] - m_matrix[1] * m_matrix[2];
	}
	else 
		for (auto i = 0; i < m_columns; i++)
		{
			result += m_matrix[i] * cofactor(0, i);
		}
	return result;
}
size_t Matrix::get_rows() const
{
	return m_rows;
}
size_t Matrix::get_columns() const
{
	return m_columns;
}
bool Matrix::is_empty() const
{
	return m_columns == 0 && m_rows == 0 && m_matrix == nullptr;
}
double Matrix::at(size_t row, size_t column) const
{
	if (row < m_rows && column < m_columns) 
		return *(m_matrix + row*m_columns + column);
	return 0;
}
Matrix& Matrix::operator=(const Matrix& other)
{
	if (&other != this) {
		double* tmp = nullptr;
		if (other.is_empty()) 
		{
			m_columns = m_rows = 0;
		}
		else {
			m_columns = other.m_columns;
			m_rows = other.m_rows;
			tmp = new double[m_rows * m_columns];
			std::copy(other.m_matrix, other.m_matrix + m_rows*m_columns, tmp);
		}
		__delete_m_matrix();
		m_matrix = tmp;
	}
	return *this;
}
Matrix Matrix::operator+=(const Matrix& other)
{
	if (is_empty() || other.is_empty()) return *this;
	if (m_rows != other.m_rows || m_columns != other.m_columns) {
		__delete_m_matrix();
		m_columns = m_rows = 0;
		return *this;
	}
	for (auto i = 0; i < m_rows * m_columns; i++) 
	{
		m_matrix[i] += other.m_matrix[i];
	}
	return *this;
}
Matrix Matrix::operator-=(const Matrix& other)
{
	if (is_empty() || other.is_empty()) return *this;
	if (m_rows != other.m_rows || m_columns != other.m_columns)
		return Matrix();
	for (auto i = 0; i < m_rows * m_columns; i++)
	{
		m_matrix[i] -= other.m_matrix[i];
	}
	return *this;
}
Matrix Matrix::operator*=(const double& num)
{
	if (is_empty()) return *this;
	for (auto i = 0; i < m_rows * m_columns; i++)
	{
		m_matrix[i] *= num;
	}
	return *this;
}
Matrix Matrix::operator/=(const double& num)
{
	if (is_empty()) return *this;
	for (auto i = 0; i < m_rows * m_columns; i++)
	{
		m_matrix[i] /= num;
	}
	return *this;
}
Matrix operator+(Matrix left, Matrix right)
{
	return left += right;
}
Matrix operator-(Matrix left, Matrix right)
{
	return left-=right;
}
Matrix operator*(Matrix left, double num)
{
	return left*=num;
}
Matrix operator/(Matrix left, double num)
{
	return left /= num;
}
Matrix operator*(const Matrix& left, const Matrix& right)
{
	if (left.get_columns() != right.get_rows() || left.is_empty() || right.is_empty())
		return Matrix();

	return Matrix(left.get_rows(), right.get_columns(), [left, right](size_t i, size_t j){
		double m_res = 0;
		size_t lhs_row_size = left.m_columns, rhs_row_size = right.m_columns;
		double* lhs = left.m_matrix + j * lhs_row_size, * rhs = right.m_matrix + i, *end = lhs + lhs_row_size;

		while(lhs < end)
		{
			m_res += *lhs++ * *rhs; 
			rhs += rhs_row_size;
		}
		return m_res;
	});
}
Matrix operator/(Matrix left, Matrix right)
{
	if (left.get_rows() != left.get_columns() || right.get_rows() != right.get_columns())
		return Matrix();
	return left * right.inverse();
}
std::ostream& operator<<(std::ostream& out, const Matrix& src)
{
	out << std::endl;
	for (auto ri = 0; ri < src.get_rows(); ri++) {
		for (auto ci = 0; ci < src.get_columns(); ci++)
			out << std::setw(12) << std::setprecision(4) << src.at(ri, ci);
		out << std::endl;
	}
	return out;
	// TODO: insert return statement here
}
