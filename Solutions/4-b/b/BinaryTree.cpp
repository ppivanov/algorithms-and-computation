#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using std::vector;
using std::cout;
using std::endl;
using std::queue;

BinaryTree::BinaryTree() = default;
BinaryTree::~BinaryTree() {
	destruct_tree(root);
}

void BinaryTree::destruct_tree(TreeNode* node) {
	if (node != nullptr) {
		destruct_tree(node->left);
		destruct_tree(node->right);
		delete node;
		node = nullptr;
	}
}

void BinaryTree::add(int toadd)
{
	if (root == nullptr) {
		root = new TreeNode(toadd);
		return;
	}

	queue<TreeNode*> q;
	q.push(root);

	add(toadd, q);
}
void BinaryTree::add(int toadd, queue<TreeNode*> queue)
{
	TreeNode* node = queue.front();
	queue.pop();
	if (node->left == nullptr) {
		node->left = new TreeNode(toadd);
		return;
	}
	else if (node->right == nullptr) {
		node->right = new TreeNode(toadd);
		return;
	}
	else {
		queue.push(node->left);
		queue.push(node->right);
		add(toadd, queue);
	}
}

bool BinaryTree::path_is_correct(vector<int> path) {
	int start = path[0];
	int path_size = path.size();
	if (path_size > 2 && root->left && path[1] == root->left->data) {								// left branch.. all elements at 1 .... n-1 should be LESS than the root
		for (size_t i = 1; i < path_size; i++)
		{
			if (path[i] > start) return false;
		}
	}
	if (path_size > 2 && root->right && path[1] == root->right->data) {								// right branch.. all elements at 1 .... n-1 should be GREATER than the root
		for (size_t i = 1; i < path.size(); i++)
		{
			if (path[i] < start) return false;
		}
	}
	return true;
}

bool BinaryTree::is_binary_search_tree() {
	vector<int> paths;
	bool is_ok = true;
	is_binary_search_tree(root, paths, is_ok);
	return is_ok;
}

void BinaryTree::is_binary_search_tree(TreeNode* node, vector<int> path, bool& is_ok) {
	if (is_ok == false) return;
	if (node == nullptr)
		return;

	path.push_back(node->data);

	if (node->left == nullptr && node->right == nullptr)
	{
		is_ok = path_is_correct(path);
	}
	else
	{
		is_binary_search_tree(node->left, path, is_ok);
		is_binary_search_tree(node->right, path, is_ok);
	}
}

// ****************** This adds the nodes as if the tree was a BST ****************** //
// ************* Comment out the add on line 25 to switch between them ************* //
//void BinaryTree::add(int toadd)
//{
//	if (root == nullptr) {
//		root = new TreeNode(toadd);
//		return;
//	}
//	add(toadd, root);
//}
void BinaryTree::add(int toadd, TreeNode* node)
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

// Print method source: https://stackoverflow.com/a/51730733
void BinaryTree::pretty_print() {
	pretty_print(root);
}
void BinaryTree::pretty_print(const TreeNode* node)
{
	pretty_print("", node, false);
}
void BinaryTree::pretty_print(std::string prefix, const TreeNode* node, bool isLeft)
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
