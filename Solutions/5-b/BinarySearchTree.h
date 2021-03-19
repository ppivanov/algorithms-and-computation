#pragma once
#include "TreeNode.h"
#include <string>
#include <fstream>

using std::ofstream;
using std::ifstream;

class BinarySearchTree
{
	friend class TreeNode;
public:
	BinarySearchTree();
	~BinarySearchTree();
	void destruct_tree();
	
	void add(int toadd);
	void remove(int toremove);
	int height();

	// Lab task - implement member functions
	int Serialise(ofstream& OutFile);
	int Deserialise(ifstream& InFile);
	
	void pretty_print();

private:
	void destruct_tree(TreeNode* node);

	void add(int toadd, TreeNode* node);
	void remove(int toremove, TreeNode* node);
	int height(TreeNode* node);

	const int* get_replacement_value(TreeNode* node);
	TreeNode* cut_leaf_on_left(TreeNode* node);
	void cut_leaf(int tocut, TreeNode* node);

	int Serialise (ofstream& OutFile, TreeNode * root);
	
	void pretty_print(const TreeNode* node);
	void pretty_print(std::string prefix, const TreeNode* node, bool isLeft);
	
	TreeNode* root;
};

