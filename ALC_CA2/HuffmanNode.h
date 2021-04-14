#pragma once

#include <iostream>

using namespace std;

class HuffmanTree;																			// declare class to avoid compilation errors
class HuffmanNode
{
public:
	HuffmanNode();
	HuffmanNode(char data_in);

private:
	char data = 0;																			// in-class initialization of the data members
	HuffmanTree* left = nullptr;
	HuffmanTree* right = nullptr;

	friend class HuffmanTree;
	friend ostream& operator<<(ostream& out, const HuffmanNode& node);
};

