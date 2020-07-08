﻿// Matrix.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <functional>

#define _BENCH

class Matrix {
	size_t m_rows, m_columns;
	double **m_matrix;
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
	 * double** m2_init = new int*[3];
	 * for (int i = 0; i < 3; i++)
	 * {
	 *		m2_init[i] = new int[3]
	 *		for(int j = 0; j < 3; j++)
	 *			m2_init[i][j] = 3*i + j + 1;
	 * }
	 * Matrix m2(m2_init, 3, 3); // Square matrix from dynamic memory
	 */
	explicit Matrix(double** arr2d, size_t rows, size_t cols);

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
	template <size_t R, size_t C> Matrix(double (&arr2d)[R][C]);

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
	Matrix(std::initializer_list<std::initializer_list<double>> list);
	/**
	 * Matrix m4 = {
	 *					{1, 2, 3, 4},
	 *					{2, 3, 4, 5},
	 *					{3, 4, 5, 6},
	 *                  {4, 5, 6, 7},
	 * };
	 * Matrix cofactors( 4, 4, [m4](size_t i, size_t j){return m4.cofactor(i, j);}); // Matrix with generator
	 */
	Matrix(size_t rows, size_t columns, std::function<double(size_t row, size_t column)> expr);
	Matrix(const Matrix& other);
	~Matrix();
private:
	inline void __delete_m_matrix();
public:
	Matrix transpose();
	Matrix inverse();
	double cofactor(size_t row, size_t column);
	double first_minor(size_t row, size_t column);
	double determinant();



	size_t get_rows() const;
	size_t get_columns() const;
	bool is_empty()const;
	double* operator[](size_t index) const;

	Matrix& operator=(const Matrix& other);
	Matrix operator+=(const Matrix& other);
	Matrix operator-=(const Matrix& other);
	Matrix operator*=(const double& num);
	Matrix operator/=(const double& num);
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

std::ostream& operator<<(std::ostream& out, const Matrix& src);

#include "Matrix.impl.h"
// TODO: Reference additional headers your program requires here.