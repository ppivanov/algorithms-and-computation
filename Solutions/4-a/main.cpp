#include "BinarySearchTree.h"
int main() {
	BinarySearchTree bst = BinarySearchTree();

	bst.add(5);									// root
	bst.add(4);									// root->left
	bst.add(3);									// root->left->left
	bst.add(1);									// root->left->left->left
	bst.add(-1);								// root->left->left->left->left
	bst.add(7);									// root->right
	bst.add(9);									// root->right->right
	bst.add(6);									// root->right->left
	bst.add(10);								// root->right->right->right

	std::cout << bst.height() << std::endl << std::endl;		// expected output == 4

	bst.remove(5);

	bst.print_in_order();

	return 0;
}
