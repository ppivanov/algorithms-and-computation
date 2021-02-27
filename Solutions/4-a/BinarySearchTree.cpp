#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() = default;
BinarySearchTree::~BinarySearchTree() {
	destruct_tree(root);
}

void BinarySearchTree::destruct_tree(TreeNode * node) {
	if (node != nullptr) {
		destruct_tree(node->left);
		destruct_tree(node->right);
		delete node;
	}
}

void BinarySearchTree::add(int toadd)
{
	if (root == nullptr) {
		root = new TreeNode(toadd);
		return;
	}
	add(toadd, root);
}
void BinarySearchTree::add(int toadd, TreeNode * node)
{
	if (node->data == toadd) return;

	if (toadd < node->data) {
		if (node->left == nullptr) {
			node->left = new TreeNode(toadd);
			return;
		}

		add(toadd, node->left);
	}
	else {
		if (node->right == nullptr) {
			node->right = new TreeNode(toadd);
			return;
		}
		add(toadd, node->right);
	}
}

void BinarySearchTree::remove(int toremove)
{
	std::cout << "Trying to remove " << toremove << "...\n\n";

	if (root == nullptr) return;
	remove(toremove, root);
}
void BinarySearchTree::remove(int toremove, TreeNode * node)
{
	if (node != nullptr) {
		if (toremove < node->data) {
			remove(toremove, node->left);
		}
		else if (toremove > node->data) {
			remove(toremove, node->right);
		}
		else {
			const int* replacement_data = get_replacement_value(node);
			if (replacement_data == nullptr) {
				cut_leaf(toremove, root);
				return;
			}
			node->data = *replacement_data;

			return;
		}
	}
	else {
		std::cout << toremove << " not found" << std::endl;
		return;
	}
}
const int* BinarySearchTree::get_replacement_value(TreeNode * node)
{
	if (node == nullptr) return nullptr;

	if (node->right != nullptr) {
		if (node->right->left == nullptr && node->right->right == nullptr) {				// node->right is leaf node - cut and return
			TreeNode* temp = node->right;
			node->right = nullptr;
			int data = temp->data;
			delete temp;
			return &data;
		}
		else if (node->right->left != nullptr) {
			TreeNode* temp = cut_leaf_on_left(node->right);
			int data = temp->data;
			delete temp;
			return &data;
		}
		else {
			TreeNode* temp = node->right;
			int data = temp->data;
			node->left = temp->left;														// temp->left should always be nullptr according to the flow
			node->right = temp->right;
			delete temp;
			return &data;
		}
	}
	else if (node->left != nullptr) {														// node has nothing on the right - delete and move left one level up
		TreeNode* temp = node->left;
		node->left = temp->left;
		node->right = temp->right;
		const int data = temp->data;

		delete temp;
		return &data;
	}
	return nullptr;																			// node to delete is a leaf node

}
TreeNode* BinarySearchTree::cut_leaf_on_left(TreeNode * node) {
	if (node == nullptr) return nullptr;
	if (node->left->left == nullptr && node->left->right == nullptr) {
		TreeNode* temp = node->left;														// node->left is the leaf node - cut and return
		node->left = nullptr;
		return temp;
	}
	return cut_leaf_on_left(node->left);
}
void BinarySearchTree::cut_leaf(int tocut, TreeNode * node) {
	if (node == nullptr) return;
	if (tocut < node->data) {
		if (node->left != nullptr && tocut == node->left->data) {
			delete node->left;
			node->left = nullptr;
			return;
		}
		cut_leaf(tocut, node->left);
	}
	else if (tocut > node->data) {
		if (node->right != nullptr && tocut == node->right->data) {
			delete node->right;
			node->right = nullptr;
			return;
		}
		cut_leaf(tocut, node->right);
	}
	else {																					// it should only get to this case if the root node is the only node and it needs to be deleted
		delete node;
		root = nullptr;
	}
}

void BinarySearchTree::pretty_print() {
	pretty_print(root);
}

int BinarySearchTree::height()
{
	return height(root);
}
int BinarySearchTree::height(TreeNode * node)
{
	if (node != nullptr) {
		int depthLeft = height(node->left);
		int depthRight = height(node->right);
		return std::max(depthLeft + 1, depthRight + 1);
	}
	else {
		return -1;
	}
}


// Print method source: https://stackoverflow.com/a/51730733
void BinarySearchTree::pretty_print(const std::string & prefix, const TreeNode * node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "|--" : "|__");

		// print the value of the node
		std::cout << node->data << std::endl;

		// enter the next tree level - left and right branch
		pretty_print(prefix + (isLeft ? "|   " : "    "), node->left, true);
		pretty_print(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}

void BinarySearchTree::pretty_print(const TreeNode * node)
{
	pretty_print("", node, false);
}