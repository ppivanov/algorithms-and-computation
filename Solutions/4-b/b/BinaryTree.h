#pragma once
#include "TreeNode.h"
#include <string>
#include <vector>
#include <queue>
using std::vector;
using std::queue;

class BinaryTree
{
	friend class TreeNode;
public:
	BinaryTree();
	~BinaryTree();
	
	void add(int toadd);
	bool is_BST();
	bool is_BST_Recur();

	void pretty_print();

private:
	void destruct_tree(TreeNode* node);

	void add(int toadd, queue<TreeNode*> queue); 
	void add(int toadd, TreeNode* node);

	int is_BST(TreeNode* node, vector<int>);
	bool path_is_correct(vector<int> path);
	int is_BST_Recur(TreeNode* node, int& min, int& max) ;

	int min_value(TreeNode* node);
	int min_value_unordered(TreeNode* node, int& min);
	int max_value_unordered(TreeNode* node, int& max);

	void pretty_print(const TreeNode* node);
	void pretty_print(std::string prefix, const TreeNode* node, bool isLeft);
	
	TreeNode* root;
};

