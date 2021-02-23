#include <iostream>
#include <string>
#include <vector>

using std::vector;

void test_quicksort();
void test_merge_sort();

int main()
{
	printf("Quick sort *************\n");
	test_quicksort();

	printf("\nMerge sort *************\n");
	test_merge_sort();

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

// Task 1a
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

// Task 1b
void quicksort(int* the_array, int size) {
	if (size > 0) {
		int pivot_index = quickSortDivide(the_array, size);

		quicksort(the_array, pivot_index);									// left
		quicksort(&the_array[pivot_index + 1], size - (pivot_index + 1));		// right
	}
}

void test_quicksort() {
	int numbers[9] = { 1, 2, 7, 6, 3, 9, 4, 5, 6 };
	int* ptr = numbers;

	print_array(ptr, 9, "Unsorted");
	quicksort(ptr, 9);
	print_array(ptr, 9, "Sorted");
}

// Task 2b
void merge(int array[], int start_index, int length) {
	const int MID = start_index + (length / 2);
	const int START = start_index;

	int middle_index = MID;

	vector<int> temp_vector;

	while (start_index < MID && middle_index < (length + START)) {
		if (array[start_index] > array[middle_index]) {
			temp_vector.push_back(array[middle_index]);
			middle_index++;
		}
		else {
			temp_vector.push_back(array[start_index]);
			start_index++;
		}
	}

	while (start_index < MID) {
		temp_vector.push_back(array[start_index]);
		start_index++;
	}

	while (middle_index < (length + START)) {
		temp_vector.push_back(array[middle_index]);
		middle_index++;
	}

	start_index = START;
	for (int i = 0; start_index < (length + START); start_index++, i++) {
		array[start_index] = temp_vector[i];
	}
}

// Task 2a
void merge_sort(int the_array[], int start_index, int length) {
	if (length <= 1) return;

	int middle_index = start_index + (length / 2);

	merge_sort(the_array, start_index, middle_index - start_index);									//left		
	merge_sort(the_array, middle_index, length - (middle_index - start_index));						//right

	merge(the_array, start_index, length);
}

void test_merge_sort() {
	int numbers[9] = { 1, 4, 3, 2, 7, 3, 8, 4, 1 };
	
	int* ptr = numbers;

	print_array(ptr, 9, "Unsorted");

	merge_sort(numbers, 0, 9);

	print_array(ptr, 9, "Sorted");
}
