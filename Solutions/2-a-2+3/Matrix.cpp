#include "Matrix.h"

using namespace std;

// I tried looking into making a 'template' function that will loop over the matrix
// in order to avoid the duplication of the double for loops that will accept a 
// single function as a parameter but that didn't work out as each case requires
// a unique function call at a different place.

template <typename T>
Matrix<T>::Matrix() {
	for (size_t i = 0; i < matrixSize; i++)
	{
		matrix.push_back({});
		for (size_t j = 0; j < matrixSize; j++)
		{
			matrix[i].push_back(0);
		}
	}
}

template <typename T>
Matrix<T>::~Matrix() = default;

template <typename T>
void Matrix<T>::print() {
	for (size_t i = 0; i < matrixSize; i++)
	{
		for (size_t j = 0; j < matrixSize; j++)
		{
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
}

template <typename T>
void Matrix<T>::setMatrix(const vector<vector<T>>& matrixIn) {
	if (matrixIn.size() != matrixSize || matrixIn[0].size() != matrixSize) {
		return;
	}
	for (size_t i = 0; i < matrixSize; i++)
	{
		for (size_t j = 0; j < matrixSize; j++)
		{
			matrix[i][j] = matrixIn[i][j];
		}
	}
}
