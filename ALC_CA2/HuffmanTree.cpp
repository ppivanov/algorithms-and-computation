#include "HuffmanTree.h"

using namespace std;

HuffmanTree::HuffmanTree() = default;

HuffmanTree::HuffmanTree(char data_in, int weight_in) :
	weight{ weight_in },
	root{ new HuffmanNode(data_in) } {  }

HuffmanTree::HuffmanTree(HuffmanTree* left_tree, HuffmanTree* right_node, int total_weight) :
	weight{ total_weight },
	root{ new HuffmanNode() } {

	root->left = left_tree;
	root->right = right_node;
};

bool CompareHuffmanTree::operator() (const HuffmanTree* lhs, const HuffmanTree* rhs) const
{
	return lhs->weight > rhs->weight;
}

bool operator<(const HuffmanTree& lhs, const HuffmanTree& rhs) {
	return lhs.weight > rhs.weight;															// Inverted so that the Trees are sorted in ascending order in the priority queue
}																							// This can be confusing to readers. TODO: refactor this to a comparator function instead

ostream& operator<<(ostream& out, const HuffmanTree& tree) {
	if ( &tree != nullptr && tree.root != nullptr) {
		out << tree.weight;
		out << *tree.root;
	}

	return out;
}

