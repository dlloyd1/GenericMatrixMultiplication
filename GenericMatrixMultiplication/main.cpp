#include <iostream>
#include "generic-matrix.h"


int main()
{
	const auto rows = 4u;
	const auto cols = 4u;

	auto testMatrix = GenericMatrix<int>{ rows, cols };
	testMatrix.printMatrix();

	testMatrix.setData({ {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} });
	testMatrix.printMatrix();

	return 0;
}
