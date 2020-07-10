// Matrix.cpp : Defines the entry point for the application.
//

#include "Matrix.h"
#include <iomanip> // for std::setw()

Matrix::Matrix() :m_rows(0), m_columns(0), m_matrix(nullptr)
{
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Constructor empty matrix " << this << std::endl;
#endif
}
Matrix::Matrix(size_t rows, size_t columns) : m_rows(rows), m_columns(columns), m_matrix(new double[m_rows * m_columns])
{
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Constructor zero matrix " << this << std::endl;
#endif
	for (auto i{ 0 }; i < m_columns * m_rows; i++) m_matrix[i] = 0;
}
Matrix::Matrix(double** arr2d, size_t rows, size_t cols) : Matrix(rows, cols)
{
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Constructor from dynamic array " << this << std::endl;
#endif
	for (int i = 0; i < m_rows; i++)
	{
		const double* row_begin = arr2d[i];
		std::copy(row_begin, row_begin + m_columns, m_matrix + i * m_rows);
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
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Constructor from initializer list " << this << std::endl;
#endif
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
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Constructor with generator  " << m_matrix << std::endl;
#endif
	double* it = m_matrix, * end = m_matrix + m_rows * m_columns;
	size_t r = 0, c = 0;
	while (it < end)
	{
		*it++ = expr(r, c++);
		if (c == m_columns) c = 0, r++;
	};
}
Matrix::Matrix(const Matrix& other)
{
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Copy Constructor " << this << std::endl;
#endif
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
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "destructor " << this << std::endl;
#endif
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
	return ((row + column) & 1) ? -(first_minor(row, column)) : first_minor(row, column);
}
double Matrix::first_minor(size_t row, size_t column)
{
	if (is_empty()) return 0;
	if (m_rows != m_columns) return INFINITY;
	size_t k = 0, l = 0;
	return Matrix(m_rows - 1, m_columns - 1, [this, row, column, &k, &l](size_t i, size_t j) {
		if (i < row)  k = i;
		else k = i + 1;
		if (j < column) l = j;
		else l = j + 1;
		return *(m_matrix + k * m_columns + l);
		}).determinant();
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
	{
		int row = 0;
		while (row < m_rows && is_row_empty(row)) row++;
		if (row == m_rows) return 0;
		for (auto i = 0; i < m_columns; i++)
		{
			result += m_matrix[i] * cofactor(row, i);
		}
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
bool Matrix::is_row_empty(size_t row) const
{
	if (row >= m_rows || is_empty()) return false;
	double* begin = m_matrix + row * m_columns, * end = begin + m_columns;
	bool result = true;
	while (begin != end)
	{
		result = result && (*begin == (double)0);
		begin++;
	}
	return result;
}
bool Matrix::is_column_empty(size_t column) const
{
	if (column >= m_columns || is_empty()) return false;
	bool result = true;
	double* begin = m_matrix + column, *end = begin + m_rows * m_columns;
	while (begin < end) {
		result = result && (*begin++ == 0);
		begin += m_columns;
	}
	return result;
}
double Matrix::at(size_t row, size_t column) const
{
	if (row < m_rows && column < m_columns)
		return *(m_matrix + row * m_columns + column);
	return 0;
}

void Matrix::exchange_rows(size_t r1, size_t r2)
{
	if (r1 >= m_rows || r2 >= m_rows)
		return;
	double* dest = m_matrix + r1 * m_columns;
	double* src = m_matrix + r2 * m_columns;
	double* tmp = new double[m_columns];

	std::copy(dest, dest + m_columns, tmp);
	std::copy(src, src + m_columns, dest);
	std::copy(tmp, tmp + m_columns, src);

	delete[] tmp;
}
void Matrix::exchange_columns(size_t c1, size_t c2)
{
	Matrix tmp = transpose();
	tmp.exchange_rows(c1, c2);
	*this = tmp.transpose();
}
void Matrix::insert_zero_row(size_t row_position)
{
	if (row_position > m_rows || is_empty()) return;
	double* result = new double[(m_rows + 1) * m_columns], * tmp = result;
	double* row = new double[m_columns];
	for (int i{ 0 }; i < m_columns; i++) row[i] = 0;
	std::copy(m_matrix, m_matrix + row_position * m_columns, tmp);
	tmp += row_position * m_columns;
	std::copy(row, row + m_columns, tmp);
	tmp += m_columns;
	std::copy(m_matrix + row_position * m_columns, m_matrix + m_columns * m_rows, tmp);
	__delete_m_matrix();
	m_rows++;
	m_matrix = result;
	delete[] row;
}
void Matrix::insert_zero_column(size_t column_position)
{
	Matrix tmp = transpose();
	tmp.insert_zero_row(column_position);
	*this = tmp.transpose();
}
void Matrix::remove_zero_rows()
{
	size_t new_rows = 0;
	double* tmp = nullptr, * result = nullptr;
	if (is_empty()) return;
	for (auto i{ 0 }; i < m_rows; i++)
	{
		if (!is_row_empty(i)) {
			new_rows++;
			tmp = new double[new_rows * m_columns];
			if (result) {
				std::copy(result, result + m_columns * (new_rows - 1), tmp);
				delete[] result;
			}
			result = tmp;

			tmp += m_columns * (new_rows - 1);
			std::copy(m_matrix + i * m_columns, m_matrix + (i + 1) * m_columns, tmp);
		}
	}
	if (!new_rows) {
		m_columns = m_rows = 0;
		__delete_m_matrix();
		delete[] result;
	}
	else {
		m_rows = new_rows;
		__delete_m_matrix();
		m_matrix = result;
	}
}
void Matrix::remove_zero_columns()
{
	Matrix tmp = transpose();
	tmp.remove_zero_rows();
	*this = tmp.transpose();
}
void Matrix::adding_rows(size_t r1, size_t r2)
{
	if (r1 >= m_rows || r2 >= m_rows) return;
	double* lhs = m_matrix + r1 * m_columns, * end = lhs + m_columns;
	double* rhs = m_matrix + r2 * m_columns;
	while (lhs != end)
	{
		*lhs++ += *rhs++;
	}
}
void Matrix::substracting_rows(size_t r1, size_t r2)
{
	if (r1 >= m_rows || r2 >= m_rows) return;
	double* lhs = m_matrix + r1 * m_columns, * end = lhs + m_columns;
	double* rhs = m_matrix + r2 * m_columns;
	while (lhs != end)
	{
		*lhs++ -= *rhs++;
	}
}
void Matrix::scaling_the_row(size_t row, double scalar)
{
	if (row >= m_rows) return;
	double* lhs = m_matrix + row * m_columns, * end = lhs + m_columns;
	while (lhs != end)
	{
		*lhs++ *= scalar;
	}
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
			std::copy(other.m_matrix, other.m_matrix + m_rows * m_columns, tmp);
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

Matrix Matrix::operator-()
{
	Matrix result = *this;
	for (auto i{ 0 }; i < m_columns * m_rows; i++)
	{
		result.m_matrix[i] = -result.m_matrix[i];
	}
	return result;
}

Matrix operator+(Matrix left, Matrix right)
{
	return left += right;
}
Matrix operator-(Matrix left, Matrix right)
{
	return left -= right;
}
Matrix operator*(Matrix left, double num)
{
	return left *= num;
}
Matrix operator/(Matrix left, double num)
{
	return left /= num;
}
Matrix operator*(const Matrix& left, const Matrix& right)
{
	if (left.get_columns() != right.get_rows() || left.is_empty() || right.is_empty())
		return Matrix();

	return Matrix(left.get_rows(), right.get_columns(), [left, right](size_t i, size_t j) {
		double m_res = 0;
		size_t lhs_row_size = left.m_columns, rhs_row_size = right.m_columns;
		double* lhs = left.m_matrix + j * lhs_row_size, * rhs = right.m_matrix + i, * end = lhs + lhs_row_size;

		while (lhs < end)
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

bool operator==(const Matrix& left, const Matrix& right)
{
	bool result = left.m_rows == right.m_rows && right.m_columns == left.m_columns;
	if (left.m_columns == 0 || right.m_columns == 0 || !result) return result;

	for (auto i{ 0 }; i < left.m_rows * left.m_columns; i++)
	{
		result = result && left.m_matrix[i] == right.m_matrix[i];
	}
	return result;
}
bool operator!=(const Matrix& left, const Matrix& right)
{
	return !(left == right);
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
