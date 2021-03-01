#pragma once

class TreeNode
{
	friend class BinaryTree;
public:
	TreeNode();
	TreeNode(int data);
	~TreeNode();

private:
	int data;
	TreeNode* left;
	TreeNode* right;
};
