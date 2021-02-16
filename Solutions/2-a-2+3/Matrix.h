#pragma once

#include <iostream>
#include <vector>

using std::vector;

template <typename T>
class Matrix {
public:
	Matrix();
	~Matrix();
	void print();
	void setMatrix(const vector<vector<T>>&);
private:
	const int matrixSize = 3;
	vector<vector<T>> matrix;
};
