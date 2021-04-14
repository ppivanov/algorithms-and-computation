#pragma once
#include "HuffmanNode.h"

class HuffmanTree
{
public:
	HuffmanTree();
	HuffmanTree(char data_in, int weight_in);

	friend bool operator<(const HuffmanTree& lhs, const HuffmanTree& rhs);
private:
	int weight = -1;													// in-class initialization of the data members
	HuffmanNode* root = nullptr;

	friend class TextCompression;
};
