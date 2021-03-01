#include "BinarySearchTree.h"
#include <iostream>

int main() {
	BinarySearchTree bst = BinarySearchTree();

	int numberToDelete = 43;
	/*
	for (size_t i = 0; i < 10; i++)
	{
		int numberToAdd = rand() % 40;
		if (i == 5) numberToDelete = numberToAdd;
		
		bst.add(numberToAdd);
	}*/

	bst.add(6);
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
	bst.add(32);

	bst.pretty_print();

	bst.pretty_print();

	return 0;
}
