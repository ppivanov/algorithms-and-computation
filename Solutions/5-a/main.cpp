#include "TemplatedHeap.h"
#include "TemplatedHeap.cpp"
#include <random>

int main() {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);

	std::vector<int> vect;

	// Test iterative trickle functions
	TemplatedHeap<int> heap = TemplatedHeap<int>();
	for (int i = 0; i < 1000; i++) {
		const int randomInt = distribution(generator);																// generates number that fits in an integer variable
		heap.insert(randomInt);					 
		vect.push_back(randomInt);
	}


	clock_t start = clock();
	heap.heapSort();
	clock_t end = clock();

	long double execution_time = 1000 * ((long double)end - start) / CLOCKS_PER_SEC;
	cout << "Time to complete ITERATIVE heap sort: " << execution_time << " ms\n";

	// Test recursive trickle functions
	TemplatedHeap<int> heap2 = TemplatedHeap<int>();
	for (int i = 0; i < 1000; i++)
		heap2.insert(distribution(generator));					 // generates number that fits in an integer variable

	clock_t start2 = clock();
	heap2.heapSortRec();
	clock_t end2 = clock();

	long double execution_time2 = 1000 * ((long double)end2 - start2) / CLOCKS_PER_SEC;
	cout << "Time to complete RECURSIVE heap sort: " << execution_time2 << " ms\n\n";

	// Default vector sort
	clock_t start3 = clock();
	std::sort(vect.begin(), vect.end());
	clock_t end3 = clock();

	long double execution_time3 = 1000 * ((long double)end3 - start3) / CLOCKS_PER_SEC;
	cout << "Time to complete std::sort on vector: " << execution_time3 << " ms\n\n";

	TemplatedHeap<char> charHeap = TemplatedHeap<char>();

	charHeap.insert('o');
	charHeap.insert('s');
	charHeap.insert('g');
	charHeap.insert('a');
	charHeap.insert('b');
	charHeap.insert('d');
	charHeap.insert('c');
	charHeap.insert('z');

	charHeap.display();

	charHeap.remove();

	charHeap.display();

	charHeap.heapSort();

	charHeap.displayAsArray();

	return 0;
}