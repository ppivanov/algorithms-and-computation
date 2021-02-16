#include <iostream>
#include <cmath>
#include "Matrix.h"
#include "Matrix.cpp"

using namespace std;

template <typename T>
int hey(const T& numberOne, const T& numberTwo) {			// changing the return type to be template type T causes the function to not work with characters
	return abs(numberOne - numberTwo);
}

int main()
{
	cout << "Labsheet 2A - part 2" << endl;
	cout << hey(10, 20) << endl;
	cout << hey(10.5, 20.5) << endl;
	cout << hey('a', 'c') << endl;

	cout << "\nLabsheet 2A - part 3" << endl;
	Matrix<int> intMatrix = Matrix<int>();

	cout << "\n----------------------\n"
		 << "Int matrix contents:" << endl;
	intMatrix.print();

	intMatrix.setMatrix({ {1,2,3}, {4,5,6}, {7,8,9} });
	
	cout << "\nAfter setting new values to Int matrix:"<<endl;
	intMatrix.print();

	Matrix<float> floatMatrix = Matrix<float>();

	cout << "\n----------------------\n"
		 << "Float matrix contents:" << endl;
	floatMatrix.print();

	floatMatrix.setMatrix({ {1.0F,2.0F,3.0F}, {4.0F,5.0F,6.0F}, {7.0F,8.0F,9.0F} });

	cout << "\nAfter setting new values to Float matrix:" << endl;
	floatMatrix.print();

	Matrix<double> doubleMatrix = Matrix<double>();

	cout << "\n----------------------\n"
		 << "Double matrix contents:" << endl;
	doubleMatrix.print();

	doubleMatrix.setMatrix({ {1.1,2.1,3.0}, {4.0,5.0,6.0}, {7.0,8.0,9.0} });

	cout << "\nAfter setting new values to Double matrix:" << endl;
	doubleMatrix.print();


	return 0;
}
