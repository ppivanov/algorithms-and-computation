#include "BinarySearchTree.h"
#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

BinarySearchTree::BinarySearchTree() = default;
BinarySearchTree::~BinarySearchTree() {
	destruct_tree(root);
}

void BinarySearchTree::destruct_tree(TreeNode * node) {
	if (node != nullptr) {
		destruct_tree(node->left);
		destruct_tree(node->right);
		delete node;
		node = nullptr;
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

void is_vectorsum_eq_sum(const vector<int>& path, int sum, bool& path_exists) {
	int path_sum = 0;
	cout << "\nPath: ";
	for (int i = 0; i < path.size(); i++) {
		path_sum += path[i];
		cout << path[i] << " ";
	}
	cout << "\b, sum: " << path_sum << endl;
	path_exists = (sum == path_sum);
}

// Function source: https://www.geeksforgeeks.org/given-a-binary-tree-print-all-root-to-leaf-paths/
// Accessed: 3 Mar, 2021
int BinarySearchTree::has_path_sum(int sum) {
	return has_path_sum(root, sum);
}
int BinarySearchTree::has_path_sum(TreeNode* node, int sum) {
	vector<int> paths;
	bool path_exists = false;
	path_recursively(root, paths, sum, path_exists);
	return path_exists;
}
void BinarySearchTree::path_recursively(TreeNode* node, vector<int> path, int sum, bool& path_exists)
{
	if (path_exists) return;
	if (node == nullptr)
		return;

	path.push_back(node->data);

	if (node->left == nullptr && node->right == nullptr)
	{
		is_vectorsum_eq_sum(path, sum, path_exists);
	}
	else
	{
		path_recursively(node->left, path, sum, path_exists);
		path_recursively(node->right, path, sum, path_exists);
	}
}

// Print method source: https://stackoverflow.com/a/51730733
void BinarySearchTree::pretty_print() {
	pretty_print(root);
}
void BinarySearchTree::pretty_print(const TreeNode * node)
{
	pretty_print("", node, false);
}
void BinarySearchTree::pretty_print(std::string prefix, const TreeNode * node, bool isLeft)
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
