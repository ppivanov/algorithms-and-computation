#include <iostream>
#include "BinarySearchTree.h"

int main() {
	
	BinarySearchTree bst = BinarySearchTree();

	for (size_t i = 0; i < 200; i++)
	{
		int numberToAdd = rand() % 57 + 66;

		bst.add(numberToAdd);
	}

	std::cout << "IN order traversal:\n";
	bst.print_in_order();

	std::cout << "\n\nPRE order traversal:\n" << std::endl;
	bst.print_pre_order();
	
	std::cout << "\n\nPOST order traversal:\n" << std::endl;
	bst.print_post_order();
	return 0;
}