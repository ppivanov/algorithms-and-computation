#pragma once
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <functional>

class BinarySearchTree
{
	friend class TreeNode;
public:
	BinarySearchTree();
	~BinarySearchTree();
	
	void add(int toadd);
	void remove(int toremove);
	int height();
	
	void pretty_print();

private:
	void destruct_tree(TreeNode* node);

	void add(int toadd, TreeNode* node);
	void remove(int toremove, TreeNode* node);
	int height(TreeNode* node);

	TreeNode* get_nearest_small_node(TreeNode* node);
	TreeNode* get_nearest_big_node(TreeNode* node);

	bool left_side_condition(TreeNode* node_to_delete, TreeNode* nearest_node);
	bool right_side_condition(TreeNode* node_to_delete, TreeNode* nearest_node);
	void remove_template(int toremove, TreeNode*& node, bool (BinarySearchTree::* c)(TreeNode*, TreeNode*), TreeNode* (BinarySearchTree::* f)(TreeNode*), BinarySearchTree bst);
	
	void pretty_print(const TreeNode* node);
	void pretty_print(const std::string& prefix, const TreeNode* node, bool isLeft);
	
	TreeNode* root;
};

