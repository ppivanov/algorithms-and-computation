#include "BinarySearchTree.h"
#include <iostream>

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

void BinarySearchTree::add(char toadd)
{
	if (root == nullptr) {
		root = new TreeNode(toadd);
		return;
	}
	add(toadd, root);
}
void BinarySearchTree::add(char toadd, TreeNode* node)
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

void BinarySearchTree::print_in_order() {
	print_in_order(root);
}
void BinarySearchTree::print_pre_order() {
	print_pre_order(root);
}
void BinarySearchTree::print_post_order() {
	print_post_order(root);
}

void BinarySearchTree::print_in_order(TreeNode* node) {
	if (node != nullptr) {
		print_in_order(node->left);
		std::cout << node->data << "\t";
		print_in_order(node->right);
	}
}

void BinarySearchTree::print_pre_order(TreeNode* node) {
	if (node != nullptr) {
		std::cout << node->data << "\t";
		print_pre_order(node->left);
		print_pre_order(node->right);
	}
}

void BinarySearchTree::print_post_order(TreeNode* node) {
	if (node != nullptr) {
		print_post_order(node->left);
		print_post_order(node->right);
		std::cout << node->data << "\t";
	}
}