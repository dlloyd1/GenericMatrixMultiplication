#ifndef GENERIC_MATRIX_PRODUCT_H
#define GENERIC_MATRIX_PRODUCT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>

template <typename T>
class GenericMatrix 
{
public:
	explicit GenericMatrix(const unsigned rows, const unsigned cols) : m_rows(rows), m_cols(cols)
	{
		assert(rows != 0);
		assert(cols != 0);

		m_data.resize(m_rows);
		for (unsigned row = 0; row < m_rows; ++row)
		{
			m_data.at(row).resize(m_cols);
		}
	};

	void printMatrix() const
	{
		for (unsigned row = 0; row < m_rows; ++row)
		{
			std::cout << "|";
			for (unsigned col = 0; col < m_cols; ++col)
			{
				std::cout << m_data.at(row).at(col);
				if (col != m_cols - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "|\n";
		}
		std::cout << "\n";
	}

	void setData(const std::vector<std::vector<T>>& val) { m_data = val; }
	std::vector<std::vector<T>> getData() const { return m_data; }

	unsigned getRows() const { return m_rows; }
	unsigned getCols() const { return m_cols; }

	GenericMatrix<T>& operator*(GenericMatrix<T>& rhs)
	{
		assert(this->getCols() == rhs.getRows());

		auto result = new GenericMatrix<T>{ this->getRows(), rhs.getCols() };

		if (this->isZeroMatrix() || rhs.isZeroMatrix())
		{
			return *result;
		}

		if (this->isIdentityMatrix() && !rhs.isIdentityMatrix())
		{
			return rhs;
		}

		if (!this->isIdentityMatrix() && rhs.isIdentityMatrix())
		{
			return *this;
		}

		std::vector<std::vector<T>> resultData;

		for (unsigned lrow = 0; lrow < this->getRows(); ++lrow)
		{
			const auto lhRow = this->m_data.at(lrow);
			std::vector<T> resultRow;
			std::vector<T> rhCol;

			for (unsigned rcol = 0; rcol < rhs.getCols(); ++rcol)
			{
				for (unsigned rrow = 0; rrow < rhs.getRows(); ++rrow)
				{
					rhCol.push_back(rhs.m_data.at(rrow).at(rcol));
				}
				resultRow.push_back(std::inner_product(lhRow.begin(), lhRow.end(), rhCol.begin(), static_cast<T>(0)));
				rhCol.clear();
			}
			resultData.push_back(resultRow);
		}
		result->setData(resultData);
		return *result;
	}

private:

	bool isZeroMatrix() const
	{
		for (unsigned row = 0; row < m_rows; ++row)
		{
			if (std::any_of(m_data.at(row).begin(), m_data.at(row).end(), [](const auto cellVal) {return cellVal != 0; }))
			{
				return false;
			}
		}
		return true;
	}

	bool isIdentityMatrix() const
	{
		if (m_rows != m_cols)
		{
			return false;
		}

		for (unsigned row = 0; row < m_rows; ++row)
		{
			for (unsigned col = 0; col < m_cols; ++col)
			{
				if (col == row)
				{
					if (m_data.at(row).at(col) != 1)
					{
						return false;
					}
				}
				else
				{
					if (m_data.at(row).at(col) != 0)
					{
						return false;
					}
				}
			}
		}
		return true;
	}


	std::vector<std::vector<T>> m_data;

	unsigned m_rows;
	unsigned m_cols;
};

#endif // GENERIC_MATRIX_PRODUCT_H