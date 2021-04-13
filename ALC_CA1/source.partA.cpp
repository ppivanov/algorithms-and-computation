// Pavel Ivanov x00149863

#include <algorithm>
#include <iostream>

template<typename T>
void quickSort(T arr[], int low, int high);
template<typename T>
int partition(T arr[], int low, int high);

//int main() {
//	
//	const int arrSize = 8;
//
//	// Test INT array
//	std::cout << "Test quicksort with integers:\n";
//	int arr[] = { 8, 10, 2, 1, 6, 23, 14, 5 };
//
//	std::cout << "Array before sorting:\n";
//	for (int i = 0; i < arrSize; i++) {
//		std::cout << arr[i] << "\t";
//	}
//
//	std::cout << "\n\nRunning array through quicksort....\n\n";
//	quickSort(arr, 0, arrSize);
//
//	std::cout << "Array after sorting:\n";
//	for (int i = 0; i < arrSize; i++) {
//		std::cout << arr[i] << "\t";
//	}
//
//	// Test DOUBLE array
//	std::cout << "\n\nTest quicksort with doubles:\n";
//	double arr_d[] = { 8.0, 10.0, 2.0, 1.0, 6.0, 23.0, 14.0, 5.0};
//
//	std::cout << "Array before sorting:\n";
//	for (int i = 0; i < arrSize; i++) {
//		std::cout << arr_d[i] << "\t";
//	}
//
//	std::cout << "\n\nRunning array through quicksort....\n\n";
//	quickSort(arr_d, 0, arrSize);
//
//	std::cout << "Array after sorting:\n";
//	for (int i = 0; i < arrSize; i++) {
//		std::cout << arr_d[i] << "\t";
//	}
//
//	return 0;
//}

// How to improve this quick sort:

// This quicksort algorithm can be improved by making it half as recursive
// This can be done by invoking a recursive call on the smaller half of the the array
// and reiterate for the bigger one.
// This will reduce the call stack and can be implemented to 
// utilize tail recursion which will improve performance overall.

// Selecting the pivot is cruicial to this algorithm's performance.
// Best option is to choose one at random.

// Using other sorting algorithm if there aren't that many elements in the array.

template<typename T>
void quickSort(T arr[], int low, int high) {
	if (low < high) {
		int midIndex = partition(arr, low, high);

		quickSort(arr, low, midIndex);
		quickSort(arr, midIndex + 1, high);
	}
}

template<typename T>
int partition(T arr[], int low, int high) {
	int mid_index = (low + high) / 2;
	const T pivot = arr[mid_index];
	int tailing_index = low - 1;

	for (int leading_index = low; leading_index < high; leading_index++) {
		if (arr[leading_index] < pivot) {
			++tailing_index;
			std::swap(arr[tailing_index], arr[leading_index]);
		}
	}
	std::swap(arr[++tailing_index], arr[mid_index]);

	return tailing_index;
}

