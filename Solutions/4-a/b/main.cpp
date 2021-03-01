#include <iostream>
#include "BinarySearchTree.h"

int main() {
	
	BinarySearchTree bst = BinarySearchTree();

	char randomCharacterInTree;
	for (size_t i = 0; i < 200; i++)
	{
		int charToAdd = (char)(rand() % 57 + 66);
		if (i == 153) randomCharacterInTree = charToAdd;

		bst.add(charToAdd);
	}

	std::cout << std::boolalpha;
	printf("Searching for existing character (%c)...\n", randomCharacterInTree);
	std::cout << bst.find(randomCharacterInTree) << std::endl;


	printf("Searchig for character that isn't in the tree (%c)...\n", '+');
	std::cout << bst.find('+') << std::endl;

	std::cout << "\nIN order traversal:\n";
	bst.print_in_order();

	std::cout << "\n\nPRE order traversal:\n" << std::endl;
	bst.print_pre_order();
	
	std::cout << "\n\nPOST order traversal:\n" << std::endl;
	bst.print_post_order();
	return 0;
}