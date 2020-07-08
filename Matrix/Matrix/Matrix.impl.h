template <size_t R, size_t C> Matrix::Matrix(double(&arr2d)[R][C]) : Matrix(R, C)
{
	std::cout << "Constructor from static array " << this << std::endl;

	for (int i = 0; i < m_rows; i++)
	{
		const double* row_begin = arr2d[i];
		std::copy(row_begin, row_begin + m_columns, m_matrix + i*m_columns);
	}
};