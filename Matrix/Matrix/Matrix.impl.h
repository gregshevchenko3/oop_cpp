template <size_t R, size_t C> Matrix::Matrix(Fraction(&arr2d)[R][C]) : Matrix(R, C)
{
#if defined(_DEBUG) && !defined (_BENCH)
	std::cout << "Constructor from static array " << this << std::endl;
#endif
	for (int i = 0; i < m_rows; i++)
	{
		const Fraction* row_begin = arr2d[i];
		std::copy(row_begin, row_begin + m_columns, m_matrix + i*m_columns);
	}
};