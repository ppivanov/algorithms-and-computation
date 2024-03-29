#pragma once

#include <iostream>

using namespace std;

class HuffmanTree;																			// declare class to avoid compilation errors
class HuffmanNode
{
public:
	HuffmanNode();
	HuffmanNode(int data_in);

private:
	int data = 0;																			// in-class initialization of the data members
	HuffmanTree* left = nullptr;
	HuffmanTree* right = nullptr;

	friend class HuffmanTree;
	friend class TextCompression;
	friend ostream& operator<<(ostream& out, const HuffmanNode& node);
};

