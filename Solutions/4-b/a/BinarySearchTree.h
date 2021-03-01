#pragma once
#include "TreeNode.h"
#include <string>
#include <vector>
using std::vector;

class BinarySearchTree
{
	friend class TreeNode;
public:
	BinarySearchTree();
	~BinarySearchTree();
	
	void add(int toadd);

	int has_path_sum(int sum);

	void pretty_print();

private:
	void destruct_tree(TreeNode* node);

	void add(int toadd, TreeNode* node);

	int has_path_sum(TreeNode* node, int sum); 
	void path_recursively(TreeNode* node, vector<int> path, int sum, bool& path_exists);

	void pretty_print(const TreeNode* node);
	void pretty_print(std::string prefix, const TreeNode* node, bool isLeft);
	
	TreeNode* root;
};

