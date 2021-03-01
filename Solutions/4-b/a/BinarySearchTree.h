#pragma once
#include "TreeNode.h"
#include <string>

class BinarySearchTree
{
	friend class TreeNode;
public:
	BinarySearchTree();
	~BinarySearchTree();
	
	void add(int toadd);

	int hasPathSum(int sum);

	void pretty_print();

private:
	void destruct_tree(TreeNode* node);

	void add(int toadd, TreeNode* node);

	int hasPathSum(TreeNode* node, int sum);

	void pretty_print(const TreeNode* node);
	void pretty_print(std::string prefix, const TreeNode* node, bool isLeft);
	
	TreeNode* root;
};

