#pragma once
#include "HuffmanNode.h"
#include <iostream>
#include <string>

using namespace std;

class HuffmanTree
{
public:
	HuffmanTree();
	HuffmanTree(char data_in, int weight_in);
	HuffmanTree(HuffmanTree* left_tree, HuffmanTree* right_node, int total_weight);

private:

	HuffmanNode *root;
	int weight = -1;																		// in-class initialization of the data members

	string get_path_to_char(char to_find);
	string get_path_to_char(char to_find, HuffmanNode* tree, string path);

	friend class TextCompression;
	friend class CompareHuffmanTree;
	friend ostream& operator<<(ostream& out, const HuffmanTree& tree);
};

class CompareHuffmanTree
{
public:
	bool operator() (const HuffmanTree* lhs, const HuffmanTree* rhs) const;
};