#include "HuffmanTree.h"

HuffmanTree::HuffmanTree() = default;

HuffmanTree::HuffmanTree(char data_in, int weight_in) :
	weight{ weight_in },
	root{ new HuffmanNode(data_in) } {  }

bool operator<(const HuffmanTree & lhs, const HuffmanTree & rhs) {
	return lhs.weight < rhs.weight;
}