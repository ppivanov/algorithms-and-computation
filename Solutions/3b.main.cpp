#include <iostream>
#include <string>
#include <vector>
#define BIG_ARR_SIZE 10000000
#define SMALL_ARR_SIZE 100000

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

void test_quicksort_big_array_random_ints();								// Task 1a
void test_quicksort_sorted_array();											// Task 1b

int main()
{
	test_quicksort_big_array_random_ints();

	test_quicksort_sorted_array();

	return 0;
}

template <typename T>
void print_array(T* array, const int& size, const std::string& type) {
	printf("\n%s array:\n", type.c_str());
	for (int i = 0; i < size; i++) {
		printf("%d\t", array[i]);
	}
	printf("\n");
}

void swap(int* value_one, int* value_two) {
	int temp = *value_one;
	*value_one = *value_two;
	*value_two = temp;
}

// Insertion sort source code: https://www.geeksforgeeks.org/insertion-sort/
void insertionsort(int* the_array, int size)
{
	int i = 1;
	int j;
	int key;
	for (; i < size; i++)
	{
		key = the_array[i];
		int j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && the_array[j] > key)
		{
			the_array[j + 1] = the_array[j];
			j = j - 1;
		}
		the_array[j + 1] = key;
	}
}

int quickSortDivide(int* the_array, int size) {
	int mid_index = size / 2;
	const int pivot = the_array[mid_index];
	int tailing_index = -1;

	for (size_t leading_index = 0; leading_index < size; leading_index++) {
		if (the_array[leading_index] < pivot) {
			swap(&the_array[++tailing_index], &the_array[leading_index]);
		}
	}
	swap(&the_array[++tailing_index], &the_array[mid_index]);

	return tailing_index;
}

void quicksort(int* the_array, int size) {
	while (size > 0) {
		if (size < 10) {
			insertionsort(the_array, size);
			break;
		}
		int pivot_index = quickSortDivide(the_array, size);

		if (pivot_index < size - (pivot_index + 1)) {							// left side is smaller - do a recursive call for the left and reiterate for the right
			the_array = &the_array[pivot_index + 1];
			size = size - (pivot_index + 1);
			quicksort(the_array, pivot_index);										
		}
		else {																	// right side is smaller - do a recursive call for the right side and reiterate for left
			size = pivot_index;
			quicksort(&the_array[pivot_index + 1], size - (pivot_index + 1));		
		}
	}
}

void test_quicksort_big_array_random_ints() {

	int* ptr = new int[BIG_ARR_SIZE];
	for (size_t i = 0; i < BIG_ARR_SIZE; i++) {
		ptr[i] = rand() % BIG_ARR_SIZE;
	}
	printf("Initialized big array of psuedo-random integers\n");
	printf("Sorting...\n");

	double start_cpu = get_cpu_time();
	double start_wall = get_wall_time();
	quicksort(ptr, BIG_ARR_SIZE);
	double end_cpu = get_cpu_time();
	double end_wall = get_wall_time();

	printf("CPU Time: %f, Wall time: %f\n\n", end_cpu - start_cpu, end_wall - start_wall);

	delete[] ptr;
}

void test_quicksort_sorted_array() {

	int* ptr = new int[SMALL_ARR_SIZE];
	for (size_t i = 0; i < SMALL_ARR_SIZE; i++) {
		ptr[i] = i;
	}
	printf("Initialized smaller already sorted array\n");
	printf("Sorting...\n");

	double start_cpu = get_cpu_time();
	double start_wall = get_wall_time();
	quicksort(ptr, SMALL_ARR_SIZE);
	double end_cpu = get_cpu_time();
	double end_wall = get_wall_time();

	printf("CPU Time: %f, Wall time: %f\n\n", end_cpu - start_cpu, end_wall - start_wall);
	delete[] ptr;
}
