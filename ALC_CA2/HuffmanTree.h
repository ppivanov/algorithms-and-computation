#pragma once
#include "HuffmanNode.h"
#include <iostream>

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

	friend class TextCompression;
	friend class CompareHuffmanTree;
	friend ostream& operator<<(ostream& out, const HuffmanTree& tree);
	friend bool operator<(const HuffmanTree& lhs, const HuffmanTree& rhs);
};

class CompareHuffmanTree
{
public:
	bool operator() (const HuffmanTree* lhs, const HuffmanTree* rhs) const;
};
