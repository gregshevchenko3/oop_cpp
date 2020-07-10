#include "Matrix.h"
#include <functional>
#include <chrono>
#include <iomanip>

// #define MATRIX_CONSTRUCTOR_TEST
// #define MATRIX_SUMARY_SUBSTRACTION_TEST
// #define MATRIX_SCALING_MULTIPLICTION_TEST
#define MATRIX_DETERMINANT_FIRST_MINOR_COMPLEMENT_TEST
// #define MATRIX_INVERSE_TRANSPOSE_TEST
// #define MATRIX_DIVISION_TEST
// #define MATRIX_ADD_REMOVE_EMPTY_ROWS_COLUMNS_AND_EXCHANGE_ROWS_TEST
// #define MATRIX_ADDING_SUBSTRACTING_ROWS_AND_SCALING_ROW_TEST
// #define MATRIX_OPERATOR_UNARY_MINUS_AND_EQUALS_OPERATORS


int main() {
#if defined(MATRIX_CONSTRUCTOR_TEST)
	{
		double** init = new double * [3]{
					new double[3]{ 1, 0, 0 },
					new double[3]{ 0, 1, 0 },
					new double[3]{ 0, 0, 1 },
		};

		double init2d[3][2] = {
			{1, 2,},
			{4, 5,},
			{7, 8,},
		};
#ifdef _BENCH
		auto t1 = std::chrono::high_resolution_clock::now();
		for (auto i = 0; i < 10000000; i++) {
#endif
			Matrix m0;
			Matrix m1(1, 3);
			Matrix m2(init, 3, 3);
			Matrix m3 = init2d;
			// Error: initializing: cannot convert from "initializer list" to "Matrix"
			// What the "initializer list"?
			// https://en.cppreference.com/w/cpp/utility/initializer_list
			Matrix m4 = {
				{1,  2,  3,  -4},
				{5,  6,  -7,  8},
				{9,  -10, 11, 12},
				{-13, 14, 15, 16}
			};
			Matrix m5 = { {} };
			Matrix m6 = {
				{},
				{1,},
				{1, 2,},
				{1, 2, 3,},
				{1, 2, 3, 4,},
			};
#ifdef _BENCH
		}
		auto t2 = std::chrono::high_resolution_clock::now();
		auto T = (t2 - t1) / 10000000;
		std::cout << T.count() << std::endl;
#else
			std::cout << "m0 = " << m0 << std::endl;
			std::cout << "m1 = " << m1 << std::endl;
			std::cout << "m2 = " << m2 << std::endl;
			std::cout << "m3 = " << m3 << std::endl;
			std::cout << "m4 = " << m4 << std::endl;
			std::cout << "m5 = " << m5 << std::endl;
			std::cout << "m6 = " << m6 << std::endl;
#endif
			delete[] init[2];
			delete[] init[1];
			delete[] init[0];
			delete[] init;
	}
#endif
#if defined(MATRIX_SUMARY_SUBSTRACTION_TEST)
		{
			Matrix m1(1, 3);
			Matrix m2{
				{1, 0, 0,},
				{0, 1, 0,},
				{0, 0, 1,},
			};
			Matrix m3 = {
				{1, 2, -3},
				{2, 3, 4},
				{3, 4, 5},
			};
			std::cout << "m1 = " << m1 << std::endl;
			std::cout << "m2 = " << m2 << std::endl;
			std::cout << "m3 = " << m3 << std::endl;

			Matrix m = m2 + m3;
			if (m.is_empty()) std::cout << "m2 + m3 cannot computed!" << std::endl;
			else
				std::cout << "m2 + m3 = " << m << std::endl;
			m = m1 + m2;
			if (m.is_empty()) std::cout << "m1 + m2 cannot computed!" << std::endl;
			else
				std::cout << m << std::endl;

			m = m2 - m3;
			if (m.is_empty()) std::cout << "m2 - m3 cannot computed!" << std::endl;
			else
				std::cout << "m2 - m3 = " << m << std::endl;
			m = m2 - m1;
			if (m.is_empty()) std::cout << "m2 - m1 cannot computed!" << std::endl;
			else
				std::cout << "m2 - m1 = " << m << std::endl;
		}
#endif
#if defined(MATRIX_SCALING_MULTIPLICTION_TEST)
		{
			Matrix m1 = {
				{1, 2,},
				{2, 3,},
				{3, 4,},
			};
			Matrix m2 = {
				{1, 2, 3,},
				{2, 3, 4,}
			};
			std::cout << "m1 = " << m1 << std::endl;
			std::cout << "m2 = " << m2 << std::endl;
			std::cout << "m1 * 10 = " << (m1 * 10) << std::endl;
			std::cout << "m1 / 10 = " << (m1 / 10) << std::endl;
			std::cout << "m1 * m2 = " << (m1 * m2) << std::endl;
		}
#endif
#if defined(MATRIX_DETERMINANT_FIRST_MINOR_COMPLEMENT_TEST)
		{
			Matrix m1 = {
				{1, 2},
				{2, 3},
			};
			Matrix m2 = {
				{0,       0,    0,  0,    0, 0,},
				{ 1,      2,    3,  4,  0.5, 0,},
				{-2,      3,   -4,  5, -0.6, 0,},
				{-0.3, -0.4, -0.5,  6,  0.7, 0,},
				{4,       5,    6,  7, -0.8, 0,},
				{5,       6,    7,  8,  0.9, 0,},
			};
			Matrix m3 = {
				{ 1,  2,  3,  4,},
				{ 5,  6,  7,  8,},
				{ 9, 10, 11, 12,},
				{13, 14, 15, 16,},
			};

			Matrix m4 = {
				{1, 2, 3}
			};
			std::cout << "m1 = " << m1 << std::endl;
			std::cout << "m1.determinant() = " << m1.determinant() << std::endl;
			std::cout << "m2 = " << m2 << std::endl;
			std::cout << "m2.determinant() = " << m2.determinant() << std::endl << std::endl;
			std::cout << "m3 = " << m3 << std::endl;
			std::cout << "m3.determinant() = " << m3.determinant() << std::endl;
			std::cout << "m4 = " << m4 << std::endl;
			std::cout << "m4.determinant() = " << m4.determinant() << std::endl;
		}
#endif
#if defined(MATRIX_INVERSE_TRANSPOSE_TEST)
		{
			Matrix m = {
				{1, 2, -4},
				{4, 4, 4},
				{2, -2, 5},
			};
			std::cout << "m = " << m << std::endl;
			std::cout << "m.inverse() = " << m.inverse() << std::endl;
			std::cout << "m.inverse().inverse() = " << m.inverse().inverse() << std::endl;
			std::cout << "m*m.inverse () = " << (m * m.inverse()) << std::endl;
			std::cout << "m.determinant() = " << (std::string)m.determinant() << std::endl;
			Matrix m2 = {
				{2, 8,},
				{12, 7},
			};
			std::cout << "m2 = " << m2 << std::endl;
			std::cout << "m2.inverse() = " << m2.inverse() << std::endl;
			std::cout << "m2.inverse().inverse() = " << m2.inverse().inverse() << std::endl;
			std::cout << "m2*m2.inverse () = " << (m2 * m2.inverse()) << std::endl;
			std::cout << "m2.determinant() = " << (std::string)m2.determinant() << std::endl;
		}
#endif
#if defined(MATRIX_DIVISION_TEST)
		{
			Matrix m1 = {
				{1, -1, 1,},
				{-1, 1, -1,},
				{1, -1, 1,},
			};
			std::cout << "m1 = " << m1 << std::endl;
			Matrix m2 = {
				{2, -8, 9,},
				{-4, 7, -3,},
				{6, -5, 1,},
			};
			std::cout << "m2 = " << m2 << std::endl;
			std::cout << "m1/m2 = " << (m1 / m2) << std::endl;
			std::cout << "m2/m2 = " << (m2 / m2) << std::endl;
			Matrix m3 = {
				{2, 8,},
				{12, 7},
			};
			std::cout << "m3 = " << m3 << std::endl;
			std::cout << "m1/m3 = " <<
				(m1 / m3) << std::endl;
			Matrix m4 = {};

			std::cout << "m4 = " << m4 << std::endl;
			std::cout << "m1/m4 = " << (m1 / m4) << std::endl;
		}
#endif
#if defined(MATRIX_ADD_REMOVE_EMPTY_ROWS_COLUMNS_AND_EXCHANGE_ROWS_TEST)
		Matrix m44 = {
			{0, 0, 0, 0,},
			{0, 1, 0, 2,},
			{0, 0, 0, 0,},
			{0, 3, 0, 4,},
		};
		m44.remove_zero_rows();
		std::cout << m44 << std::endl;
		m44.remove_zero_columns();
		std::cout << m44 << std::endl;

		m44.insert_zero_row(1);
		std::cout << m44 << std::endl;
		m44.insert_zero_row(0);
		std::cout << m44 << std::endl;

		m44.insert_zero_column(1);
		std::cout << m44 << std::endl;
		m44.insert_zero_column(0);
		std::cout << m44 << std::endl;

		m44.exchange_rows(0, 1);
		std::cout << m44 << std::endl;
		m44.exchange_columns(0, 1);
		std::cout << m44 << std::endl;
#endif
#if defined(MATRIX_ADDING_SUBSTRACTING_ROWS_AND_SCALING_ROW_TEST)
		Matrix m44 = {
			{ 1,  2,  3,  4,},
			{ 5,  6,  7,  8,},
			{ 9, 10, 11, 12,},
			{13, 14, 15, 16,},
		};
		std::cout << m44 << std::endl;

		m44.adding_rows(1, 2);
		std::cout << m44 << std::endl;

		m44.substracting_rows(1, 0);
		std::cout << m44 << std::endl;

		m44.scaling_the_row(0, 10.0);
		std::cout << m44 << std::endl;
#endif
#if defined(MATRIX_OPERATOR_UNARY_MINUS_AND_EQUALS_OPERATORS)
		Matrix m44 = {
			{-0.1, -0.2,  0.3,  0.4,},
			{-0.5, -0.6,  0.7,  0.8,},
			{ 0.9,  1.0, -1.1, -1.2f,},
			{ 1.3,  1.5, -1.6, -1.7f,},
		};
		std::cout << m44 << std::endl;
		std::cout << -m44 << std::endl;
		std::cout << std::boolalpha << (m44 != -m44) << std::endl;
		std::cout << (m44 == m44) << std::endl;

#endif
		return 0;
}