#pragma once

class HuffmanNode
{
public:
	HuffmanNode();
	HuffmanNode(char data_in);

private:
	friend class HuffmanTree;

	char data = 0;														// in-class initialization of the data members
	HuffmanNode* left = nullptr;
	HuffmanNode* right = nullptr;
};

