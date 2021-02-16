#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define ARR_SIZE 10000000

/*********** CPU and wall times source code (9 Feb, 2020): ***********/
/*********** https://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows ***********/
#ifdef _WIN32
#include <Windows.h>
double get_wall_time() {
	LARGE_INTEGER time, freq;
	if (!QueryPerformanceFrequency(&freq)) {
		//  Handle error
		return 0;
	}
	if (!QueryPerformanceCounter(&time)) {
		//  Handle error
		return 0;
	}
	return (double)time.QuadPart / freq.QuadPart;
}
double get_cpu_time() {
	FILETIME a, b, c, d;
	if (GetProcessTimes(GetCurrentProcess(), &a, &b, &c, &d) != 0) {
		//  Returns total user time.
		//  Can be tweaked to include kernel times as well.
		return
			(double)(d.dwLowDateTime |
				((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
	}
	else {
		//  Handle error
		return 0;
	}
}
#endif
/*********** https://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows ***********/

using std::vector;

void initialize_vector(vector<int>&);
// Task 1
int binary_search_iterative(const vector<int>&, int, int, int);

// Task 2
template <typename T>																							// Constraint for this template type are the operators > and ==, meaning that any type that has these operators overloaded can be used with this function
int binary_search_recursive(const vector<T>&, int, int, T);

template <typename T>
void test_binary_search(const vector<T>&, int (*f)(const vector<T>&, int, int, T));

template <typename T>
void print_array(T*, const std::string&);

template <typename T>
void swap(T*, T*);

template<typename T>
T* quicksort(T* array, int start, int end);

void test_quicksort();

int main()
{
	vector<int> int_vector;
	initialize_vector(int_vector);

	printf("\n--------- Iterative binary search ---------\n");
	test_binary_search(int_vector, binary_search_iterative);

	printf("\n--------- Recursive binary search ---------\n");
	test_binary_search(int_vector, binary_search_recursive);

	test_quicksort();

	return 0;
}

// Observations:
// CPU time for all runs is minimal and is listed as 0.000000

/**************** Wall times ****************/
/*	Runs	|	Iterative	|	Recursive	*/
/*  --------------------------------------  */
/*	1st		|	0.000006	|	0.000003	*/
/*	2nd		|	0.000006	|	0.000002	*/
/*	3rd		|	0.000007	|	0.000004	*/
/*	4th		|	0.000007	|	0.000003	*/
/*	5th		|	0.000006	|	0.000002	*/
/*	6th		|	0.000006	|	0.000003	*/
/*	--------------------------------------  */
/********************************************/

// Average wall time for both implementations: 0.000001 (based on 10,000 runs)

// In all test runs the Recusive version of the sort algorithm performed better in terms of speed.
// In my opinion this is due to the reduced number of operations in the recursive function compared to the iterative equivalent.
// By this I mean that the lack of reassignment to the 'lowIndex' and 'highIndex' variables may be enough to reduce the speed by ~ half.

// Task 3
void initialize_vector(vector<int>& int_vector) {
	for (int i = 0; i < ARR_SIZE; i++)
		int_vector.push_back(rand());
	std::sort(int_vector.begin(), int_vector.end());
}

int binary_search_iterative(const vector<int>& arr, int low_index, int high_index, int search_value) {
	while (true) {
		int mid_index = (high_index + low_index) / 2;
		if (arr[mid_index] == search_value) return mid_index;
		if (low_index == high_index) return -1;

		if (search_value > arr[mid_index])
			low_index = mid_index + 1;
		else
			high_index = mid_index;
	}
}

template <typename T>																							// Constraint for this template type are the operators > and ==, meaning that any type that has these operators overloaded can be used with this function
int binary_search_recursive(const vector<T>& arr, int low_index, int high_index, T search_value) {
	int mid_index = (high_index + low_index) / 2;
	if (arr[mid_index] == search_value) return mid_index;
	if (low_index == high_index) return -1;

	if (search_value > arr[mid_index])
		return binary_search_recursive(arr, mid_index + 1, high_index, search_value);
	else
		return binary_search_recursive(arr, low_index, mid_index, search_value);
}

// Task 4
template <typename T>
void test_binary_search(const vector<T>& int_vector, int (*f)(const vector<T>&, int, int, T)) {

	double total_cpu = 0;
	double total_wall = 0;
	const int num_iterations = 10000;

	for (size_t i = 0; i < num_iterations; i++)
	{
		int num_to_search = rand() % ARR_SIZE;
		double start_wall = get_wall_time();
		double start_cpu = get_cpu_time();
		int index = (*f)(int_vector, 0, int_vector.size() - 1, num_to_search);
		double end_wall = get_wall_time();
		double end_cpu = get_cpu_time();

		total_cpu += (end_cpu - start_cpu);
		total_wall += (end_wall - start_wall);
	}
	printf("\nAverage CPU time: %f", total_cpu / num_iterations);
	printf("\nAverage wall time: %f\n", total_wall / num_iterations);
}

// Task 5
template <typename T>
void print_array(T* array, const std::string& type) {
	printf("\n%s array:\n", type.c_str());
	for (int i = 0; i < 9; i++) {
		printf("%d\t", array[i]);
	}
	printf("\n");
}

template <typename T>
void swap(T* value_one, T* value_two)
{
	T temp = *value_one;
	*value_one = *value_two;
	*value_two = temp;
}

// Adapted from https://www.geeksforgeeks.org/quick-sort/, 12 Feb, 2020
template<typename T>
T* quicksort(T* array, int start, int end) {
	if (start < end) {
		int mid_index = (start + end) / 2;
		const T pivot = array[mid_index];
		int tailing_index = start - 1;

		for (size_t leading_index = start; leading_index < end; leading_index++) {
			if (array[leading_index] < pivot) {
				++tailing_index;
				swap(&array[tailing_index], &array[leading_index]);
			}
		}
		swap(&array[tailing_index + 1], &array[mid_index]);

		quicksort(array, start, tailing_index);
		quicksort(array, tailing_index + 2, end);
	}
	return array;
}

void test_quicksort() {
	int numbers[9] = { 1, 2, 7, 6, 3, 9, 4, 5, 6 };
	int* ptr = numbers;

	print_array(ptr, "Unsorted");

	quicksort(ptr, 0, 9);

	print_array(ptr, "Sorted");
}
