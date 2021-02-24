#include "BinarySearchTree.h"
int main() {
	BinarySearchTree bst = BinarySearchTree();

	//bst.add(5);									// root
	//bst.add(4);									// root->left
	//bst.add(3);									// root->left->left
	//bst.add(1);									// root->left->left->left
	//bst.add(-1);								// root->left->left->left->left
	//bst.add(7);									// root->right
	//bst.add(9);									// root->right->right
	//bst.add(6);									// root->right->left
	//bst.add(10);								// root->right->right->right

	for (size_t i = 0; i < 10; i++)
	{
		bst.add(rand() % 40);
	}
		bst.add(23);
	bst.pretty_print();

	std::cout << "Height of tree: " << bst.height() << std::endl << std::endl;		// expected output == 4

	bst.remove(23);

	bst.pretty_print();

	return 0;
}
