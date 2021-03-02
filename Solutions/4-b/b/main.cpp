#include "BinaryTree.h"
#include <iostream>
#include <ctime>

using std::cout;
using std::endl;
using std::clock;
using std::clock_t;

int main() {
	cout << std::boolalpha;
	BinaryTree bst = BinaryTree();
	
	for (size_t i = 0; 
		i < 100
		//i < 1000000											// Performance test 
		; i++)
	{
		int numberToAdd = rand()
			% 100												// Comment out this line to widen the range of the values
			;
		
		bst.add(numberToAdd);
	}

	/*bst.add(6);
	bst.add(5);
	bst.add(1);
	bst.add(100);
	bst.add(21);
	bst.add(15);
	bst.add(63);
	bst.add(79);
	bst.add(43);
	bst.add(61);
	bst.add(48);
	bst.add(27);
	bst.add(24);
	bst.add(29);
	bst.add(38);
	bst.add(32);*/

	bst.pretty_print();

	clock_t start = clock();
	bool is_BST_one = bst.is_BST();																// 1,000,000 ordered elements ~ 159 ms
	clock_t end = clock();
	long double execution_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
	cout << "Binary Tree can be Binary Search Tree: " << is_BST_one << endl;
	cout << "Time to complete: " << execution_time << " ms"<< endl;										

	clock_t start2 = clock();
	bool is_BST_two = bst.is_BST_Recur();														// 1,000,000 ordered elements ~ 3-4 ms
	clock_t end2 = clock();
	long double execution_time2 = 1000.0 * (end2 - start2) / CLOCKS_PER_SEC;
	cout << "Binary Tree can be Binary Search Tree [V2]: " << is_BST_two << endl;
	cout << "Time to complete: " << execution_time2 << " ms"<< endl;							
	return 0;
}
