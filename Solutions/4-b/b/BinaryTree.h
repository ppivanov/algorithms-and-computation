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
	bool is_binary_search_tree();

	void pretty_print();

private:
	void destruct_tree(TreeNode* node);

	void add(int toadd, queue<TreeNode*> queue); 
	void add(int toadd, TreeNode* node);
	void is_binary_search_tree(TreeNode* node, vector<int>, bool& is_ok);
	bool path_is_correct(vector<int> path);

	void pretty_print(const TreeNode* node);
	void pretty_print(std::string prefix, const TreeNode* node, bool isLeft);
	
	TreeNode* root;
};

