// Matrix.cpp : Defines the entry point for the application.
//

#include "Matrix.h"
#include <iomanip> // for std::setw()

Matrix::Matrix():m_rows(0), m_columns(0), m_matrix(nullptr)
{
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Constructor zero matrix " << this << std::endl;
#endif
}
Matrix::Matrix(size_t rows, size_t columns) : m_rows(rows), m_columns(columns)
{
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Constructor zero matrix " << this << std::endl;
#endif
	m_matrix = new double* [m_rows];
	for (auto i = 0; i < m_rows; i++)
	{
		m_matrix[i] = new double[m_columns]{0};
	}
}
Matrix::Matrix(double** arr2d, size_t rows, size_t cols) : Matrix(rows, cols)
{
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Constructor from dynamic array " << this << std::endl;
#endif
	for (int i = 0; i < m_rows; i++)
	{
		const double* row_begin = arr2d[i];
		std::copy(row_begin, row_begin + m_columns, m_matrix[i]);
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
	std::cout << "Constructor from initializer_list" << this << std::endl;
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
	m_matrix = new double* [m_rows];
	for (auto i = 0; i < m_rows; i++, row_it++ ) {
		auto col_it = row_it->begin();
		auto col_end = row_it->end();
		m_matrix[i] = new double[m_columns];

		for (auto j = 0; j < m_columns; j++, col_it++) {
			m_matrix[i][j] = (col_it < col_end)? *col_it : 0;
		}
	}
}
Matrix::Matrix(size_t rows, size_t columns, std::function<double(size_t row, size_t column)> expr) : m_rows(rows), m_columns(columns)
{
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Constructor with generator " << this << std::endl;
#endif
	m_matrix = new double* [m_rows];
	for (auto i{ 0 }; i < rows; i++)
	{
		m_matrix[i] = new double[m_columns];
		for (auto j{ 0 }; j < m_columns; j++)
		{
			m_matrix[i][j] = expr(i, j);
		}
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
		m_matrix = new double*[m_rows];
		for (int i = 0; i < m_rows; i++)
		{
			m_matrix[i] = new double[m_columns];
			const double* row_begin = other[i];
			std::copy(row_begin, row_begin + m_columns, m_matrix[i]);
		}
	}
};
Matrix::~Matrix()
{
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Destructor " << this << std::endl;
#endif
	__delete_m_matrix();
}
inline void Matrix::__delete_m_matrix()
{
	if (m_matrix) {
		for (auto i = 0; i < m_rows; i++) {
			if (m_matrix[i]) {
				delete[] m_matrix[i];
			}
			m_matrix[i] = nullptr;
		}
		delete[] m_matrix;
		m_matrix = nullptr;
	}
}
Matrix Matrix::transpose()
{
	if (is_empty()) return *this;
	Matrix result(m_columns, m_rows);
	for (auto i = 0; i < m_columns; i++)
		for (auto j = 0; j < m_rows; j++)
			result[i][j] = m_matrix[j][i];
	return result;
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
	for (int i = 0; i < m_rows; i++) 
	{
		int ni;
		if (i < row) ni = i;
		if (i > row) ni = i - 1;
		if (i == row) continue;

		for (int j = 0; j < m_columns; j++)
		{
			int nj;
			if (j < column) nj = j;
			if (j > column) nj = j - 1;
			if (j == column) continue;
			result[ni][nj] = m_matrix[i][j];
		}
	}
	return result.determinant();
}
double Matrix::determinant()
{
	double result = 0;
	if (m_rows != m_columns) return INFINITY;
	if (is_empty()) return 0;
	if (m_rows == 2) {
		result = m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
	}
	else 
		for (auto i = 0; i < m_columns; i++)
		{
			result += m_matrix[0][i] * cofactor(0, i);
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
	bool result = true;
	if (row >= m_rows || is_empty()) return false;
	for (auto i{ 0 }; i < m_columns; i++)
	{
		result = result && m_matrix[row][i] == 0;
	}
	return result;
}
bool Matrix::is_column_empty(size_t column) const
{
	bool result = true;
	if (column >= m_columns || is_empty()) return false;
	for (auto i{ 0 }; i < m_rows; i++)
	{
		result = result && m_matrix[i][m_columns] == 0;
	}
	return result;
}
double* Matrix::operator[](size_t index) const
{
	if (index < m_rows) return m_matrix[index];
	return nullptr;
}
void Matrix::exchange_rows(size_t r1, size_t r2)
{
	if (r1 >= m_rows || r2 >= m_rows || r1 == r2) return;
	double* tmp = new double[m_columns];
	std::copy(m_matrix[r1], m_matrix[r1] + m_columns, tmp);
	std::copy(m_matrix[r2], m_matrix[r2] + m_columns, m_matrix[r1]);
	std::copy(tmp, tmp + m_columns, m_matrix[r2]);
	delete[] tmp;
}
void Matrix::exchange_columns(size_t c1, size_t c2)
{
	Matrix tmp = transpose();
	tmp.exchange_columns(c1, c2);
	*this = tmp.transpose();
}
void Matrix::insert_zero_row(size_t row_position)
{
	if (row_position > m_rows || is_empty())
		return;
	double** tmp = new double*[m_rows++];
	for (auto i{ 0 }; i < m_rows; i++)
	{
		tmp[i] = new double[m_columns] {0};
		if (i < row_position) 
		{
			std::copy(m_matrix[i], m_matrix[i] + m_columns, tmp[i]);
		} 
		else if (i > row_position)
		{
			std::copy(m_matrix[i - 1], m_matrix[i - 1] + m_columns, tmp[i]);
		}
	}
	__delete_m_matrix();
	m_matrix = tmp;
}
void Matrix::insert_zero_column(size_t column_position)
{
	Matrix tmp = transpose();
	tmp.insert_zero_row(column_position);
	*this = tmp.transpose();
}
void Matrix::remove_zero_rows()
{
	if (is_empty()) return;
	double** tmp{ nullptr } result{tmp};
	size_t new_rows{0}
	for (auto i{ 0 }; i < m_rows; i++)
	{
		if (!is_row_empty(i)) {
			new_rows++;
			result = new double* [new_rows];
			if (!tmp) {
				std::copy(tmp, tmp + new_rows - 1, result);
				delete [] tmp
			}
			tmp = result;
			tmp[new_rows - 1] = m_matrix[i];
		}
		else {
			delete m_matrix[i];
		}
	}
	if (!new_rows)
	{
		m_rows = m_columns = 0;
		delete[] m_matrix;
		m_matrix = result = tmp = nullptr;
	} 
	else {
		m_rows = new_rows;
		delete[] m_matrix;
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
	if (r1 >= m_rows || r2 >= m_rows)
		return;
	for (auto i{ 0 }; i < m_columns; i++)
		m_matrix[r1][i] += m_matrix[r2][i];
}
void Matrix::substracting_rows(size_t r1, size_t r2)
{
	if (r1 >= m_rows || r2 >= m_rows)
		return;
	for (auto i{ 0 }; i < m_columns; i++)
		m_matrix[r1][i] -= m_matrix[r2][i];
}
void Matrix::scaling_the_row(size_t row, double scalar)
{
	if (row >= m_rows) return;
	for (auto i{ 0 }; i < m_columns; i++)
		m_matrix[row][i] *= scalar;
}
Matrix& Matrix::operator=(const Matrix& other)
{
	if (&other != this) {
		double** tmp = nullptr;
		if (other.is_empty()) 
		{
			m_columns = m_rows = 0;
		}
		else {
			m_columns = other.m_columns;
			m_rows = other.m_rows;
			tmp = new double* [m_rows];
			for (auto i = 0; i < m_rows; i++)
			{
				tmp[i] = new double[m_columns];
				const double* row_begin = other[i];
				std::copy(row_begin, row_begin + m_columns, tmp[i]);
			}
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
	for (auto i = 0; i < m_rows; i++) 
	{
		for (auto j = 0; j < m_columns; j++)
		{
			m_matrix[i][j] += other[i][j];
		}
	}
	return *this;
}
Matrix Matrix::operator-=(const Matrix& other)
{
	if (is_empty() || other.is_empty()) return *this;
	if (m_rows != other.m_rows || m_columns != other.m_columns)
		return Matrix();
	for (auto i = 0; i < m_rows; i++)
	{
		for (auto j = 0; j < m_columns; j++)
		{
			m_matrix[i][j] -= other[i][j];
		}
	}
	return *this;
}
Matrix Matrix::operator*=(const double& num)
{
	if (is_empty()) return *this;
	for (auto i = 0; i < m_rows; i++)
	{
		for (auto j = 0; j < m_columns; j++)
		{
			m_matrix[i][j] *= num;
		}
	}
	return *this;
}
Matrix Matrix::operator/=(const double& num)
{
	if (is_empty()) return *this;
	for (auto i = 0; i < m_rows; i++)
	{
		for (auto j = 0; j < m_columns; j++)
		{
			m_matrix[i][j] /= num;
		}
	}
	return *this;
}
Matrix Matrix::operator-()
{
	for (auto i{ 0 }; i < m_rows; i++)
		for (auto j{ 0 }; j < m_columns; j++)
			m_matrix[i][j] = -m_matrix[i][j];
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
	Matrix result = { left.get_rows(), right.get_columns() };
	for (auto i = 0; i < result.get_rows(); i++)
	{
		for (auto j = 0; j < result.get_columns(); j++)
		{
			for (auto k = 0; k < left.get_columns(); k++)
			{
				result[i][j] += left[i][k] * right[k][j];
			}
		}
	}
	return result;
}
Matrix operator/(Matrix left, Matrix right)
{
	if (left.get_rows() != left.get_columns() || right.get_rows() != right.get_columns())
		return Matrix();
	return left * right.inverse();
}
bool operator==(const Matrix& left, const Matrix& right)
{
	bool result{ true };
	result = result && left.m_rows == right.m_rows && left.m_columns == right.m_columns;
	if (!result) return result;
	for (auto i{ 0 }; i < m_rows; i++)
		for (auto j{ 0 }; j < m_columns; j++)
			result = result && left[i][j] == right[i][j];
	return result;
}
std::ostream& operator<<(std::ostream& out, const Matrix& src)
{
	out << std::endl;
	for (auto ri = 0; ri < src.get_rows(); ri++) {
		for (auto ci = 0; ci < src.get_columns(); ci++)
			out << std::setw(12) << std::setprecision(4) << src[ri][ci];
		out << std::endl;
	}
	return out;
	// TODO: insert return statement here
}
