#pragma once

class TreeNode
{
	friend class BinarySearchTree;
public:
	TreeNode();
	TreeNode(char data);
	~TreeNode();

private:
	char data;
	TreeNode* left;
	TreeNode* right;
};
