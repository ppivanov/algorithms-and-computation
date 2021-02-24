#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() = default;
BinarySearchTree::~BinarySearchTree() {
	destruct_tree(root);
}

void BinarySearchTree::destruct_tree(TreeNode* node) {
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

void BinarySearchTree::remove_template(int toremove, TreeNode * &node, bool (BinarySearchTree:: * not_equal_condition)(TreeNode*, TreeNode*), TreeNode * (BinarySearchTree:: * get_nearest_node)(TreeNode*), BinarySearchTree bst) {
	if (node != nullptr) {
		if (toremove == node->data) {
			TreeNode* node_to_delete = node;
			TreeNode* nearest_leaf_node = (bst.*get_nearest_node)(node_to_delete);

			if ((bst.*not_equal_condition)(node_to_delete, nearest_leaf_node)) {
				nearest_leaf_node->left = node_to_delete->left;
				nearest_leaf_node->right = node_to_delete->right;
			}
			node = nearest_leaf_node;

			delete node_to_delete;
			return;
		}
		remove(toremove, node);
	}
	else {
		std::cout << toremove << " not found" << std::endl;
		return;
	}
}
void BinarySearchTree::remove(int toremove)
{
	if (root == nullptr) return;

	remove(toremove, root);
}
void BinarySearchTree::remove(int toremove, TreeNode * node)
{
	BinarySearchTree bst;
	if (toremove < node->data) {
		remove_template(
			toremove,
			node->left,
			&BinarySearchTree::left_side_condition,
			&BinarySearchTree::get_nearest_big_node,
			bst);
	}
	else if (toremove > node->data) {
		remove_template(
			toremove,
			node->right,
			&BinarySearchTree::right_side_condition,
			&BinarySearchTree::get_nearest_small_node,
			bst);
	}
	else {
		TreeNode* old_root = root;
		root = old_root->right;
		TreeNode* leaf_node = get_nearest_small_node(root);
		if (leaf_node != nullptr) {
			leaf_node->left = old_root->left;
			root->left = leaf_node;
		}
		else {
			root->left = old_root->left;
		}
		delete old_root;
	}
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

TreeNode* BinarySearchTree::get_nearest_small_node(TreeNode * node)
{
	if (node == nullptr) return nullptr;

	if (node->left != nullptr) {
		if (node->left->left == nullptr && node->left->right == nullptr) {
			TreeNode* temp = node->left;
			node->left = nullptr;
			return temp;
		}
		get_nearest_small_node(node->left);
	}
	else if (node->right != nullptr) {
		return node->right;
	}
	else {
		return nullptr;
	}
}
TreeNode* BinarySearchTree::get_nearest_big_node(TreeNode * node)
{
	if (node == nullptr) return nullptr;

	if (node->right != nullptr) {
		if (node->right->left == nullptr && node->right->right == nullptr) {
			TreeNode* temp = node->right;
			node->right = nullptr;
			return temp;
		}
		get_nearest_big_node(node->right);
	}
	else if (node->left != nullptr) {
		return node->left;
	}
	else {
		return nullptr;
	}
}

void BinarySearchTree::print_in_order()
{
	print_in_order(root);
}
void BinarySearchTree::print_in_order(TreeNode * node)
{
	if (node == nullptr) return;
	print_in_order(node->left);
	std::cout << node->data << std::endl;
	print_in_order(node->right);
}

bool BinarySearchTree::left_side_condition(TreeNode * node_to_delete, TreeNode * nearest_node) {
	return node_to_delete->left != nearest_node;
}
bool BinarySearchTree::right_side_condition(TreeNode * node_to_delete, TreeNode * nearest_node) {
	return node_to_delete->right != nearest_node;
}

void BinarySearchTree::pretty_print() {
	pretty_print(root);
}

void BinarySearchTree::pretty_print(const std::string& prefix, const TreeNode* node, bool isLeft)
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

void BinarySearchTree::pretty_print(const TreeNode* node)
{
	pretty_print("", node, false);
}