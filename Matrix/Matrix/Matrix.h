// Matrix.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <functional>

#include "../../Fraction/Fraction.hpp"

//#define _BENCH
class Matrix {
	size_t m_rows, m_columns;
	// double **m_matrix;
	/*
	 * https://www.cyberforum.ru/cpp-beginners/thread37687.html
	 * 4rray
	 * 8 / 8 / 2
	 * Регистрация: 15.12.2010
	 * Сообщений: 41
	 * 24.12.2010, 20:21	4
	 * Тоже самое, только предварительно умножить матрицу на саму себя, а потом вычитать.
	 * Кстати в плане быстродействия лучше хранить матрицы в одномерном массиве.
	 */
	Fraction* m_matrix;
public:
	/**
	 * Matrix m1;	// Empty matrix
	 */
	Matrix();
	/**
	 * Matrix m1 = {3, 3}	// Square matrix with 3 rows and 3 coluumns, where each element is 0.
	 */
	Matrix(size_t rows, size_t columns);
	
	/**
	 * FrACTION** m2_init = ...;
	 * for (int i = 0; i < 3; i++)
	 * {
	 *		. . . .
	 *		for(int j = 0; j < 3; j++)
	 *			. . . . 
	 * }
	 * Matrix m2(m2_init, 3, 3); // Square matrix from dynamic memory
	 */
	explicit Matrix(Fraction** arr2d, size_t rows, size_t cols);

	/**
	 * int m3_init[3][3] = {
	 *							{ 1, 2, 3},
	 *                          { 4, 5, 6},
	 *                          { 7, 8, 9},
	 * };
	 * Matrix m3 = m3_init; // Square matrix from 2d-array
	 *
	 * Зроблено за принципом реалізації std::copy(), але потрібного ефекту досягти не вдалося.
	 * Все одно спочатку потрібно створити масив, а потім передати його в конструктор, що незручно.
	 */
	template <size_t R, size_t C> Matrix(Fraction (&arr2d)[R][C]);

	/**
	 * потрібний ефект, якого я ддобивався, щоб писати так:
	 *
	 * Matrix m4 = {							// Matrix from initializer-list
	 *					{1, 2, 3, 4},
	 *					{2, 3, 4, 5},
	 *					{3, 4, 5, 6},
	 *                  {4, 5, 6, 7},
	 * };
	 * Зроблено за прикладом, що знаходиться тут:
	 *  https://en.cppreference.com/w/cpp/utility/initializer_list
	 */
	Matrix(std::initializer_list<std::initializer_list<Fraction>> list);
	/**
	 * Matrix m4 = {
	 *					{1, 2, 3, 4},
	 *					{2, 3, 4, 5},
	 *					{3, 4, 5, 6},
	 *                  {4, 5, 6, 7},
	 * };
	 * Matrix cofactors( 4, 4, [m4](size_t i, size_t j){return m4.cofactor(i, j);}); // Matrix with generator
	 */
	Matrix(size_t rows, size_t columns, std::function<Fraction(size_t row, size_t column)> expr);
	Matrix(const Matrix& other);
	~Matrix();
private:
	inline void __delete_m_matrix();
public:
	Matrix transpose();
	Matrix inverse();
	Fraction cofactor(size_t row, size_t column);
	Fraction first_minor(size_t row, size_t column);
	Fraction minor(size_t rows_indexes[], size_t columns_indexes[], size_t order);
	Fraction determinant();

	size_t get_rows() const;
	size_t get_columns() const;
	bool is_empty()const;
	bool is_row_empty(size_t row) const;
	bool is_column_empty(size_t column) const;
	Fraction at(size_t row, size_t column) const;

	void exchange_rows(size_t r1, size_t r2);
	void exchange_columns(size_t c1, size_t c2);
	void insert_zero_row(size_t row_position);
	void insert_zero_column(size_t column_position);
	void remove_zero_rows();
	void remove_zero_columns();
	void adding_rows(size_t r1, size_t r2);
	void substracting_rows(size_t r1, size_t r2);
	void scaling_the_row(size_t row, Fraction scalar);

	Matrix& operator=(const Matrix& other);
	Matrix operator+=(const Matrix& other);
	Matrix operator-=(const Matrix& other);
	Matrix operator*=(const Fraction& num);
	Matrix operator/=(const Fraction& num);

	Matrix operator-();

	friend Matrix operator*(const Matrix& left, const Matrix& right);
	friend bool operator==(const Matrix& left, const Matrix& right);
};
/**
 * Matrices adding
 */
Matrix operator+(Matrix left, Matrix right);
/**
 * Matrices substraction
 */
Matrix operator-(Matrix left, Matrix right);
/**
 * Scalar multipliation.
 */
Matrix operator*(Matrix left, double num);
/**
 * Scalar division.
 */
Matrix operator/(Matrix left, double num);
/**
 * Matrices multiplication
 */
Matrix operator*(const Matrix& left, const Matrix& right);

/** Matrices division by matrices production left and right^-1 */
Matrix operator/(Matrix left, Matrix right);
bool operator==(const Matrix& left, const Matrix& right);
bool operator!=(const Matrix& left, const Matrix& right);

std::ostream& operator<<(std::ostream& out, const Matrix& src);

#include "Matrix.impl.h"
// TODO: Reference additional headers your program requires here.
