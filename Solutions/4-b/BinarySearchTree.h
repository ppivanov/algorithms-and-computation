#pragma once
#include "TreeNode.h"

class BinarySearchTree
{
	friend class TreeNode;
public:
	BinarySearchTree();
	~BinarySearchTree();

	void add(char toadd);
	bool find(char key);

	void print_in_order();
	void print_pre_order();
	void print_post_order();

private:
	void destruct_tree(TreeNode* node);

	void add(char toadd, TreeNode* node);
	bool find(char key, TreeNode* node);

	void print_in_order(TreeNode* node);
	void print_pre_order(TreeNode* node);
	void print_post_order(TreeNode* node);

	TreeNode* root;
};

