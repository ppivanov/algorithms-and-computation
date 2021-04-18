#include "HuffmanTree.h"																	// include the class file as it was only declared in the Node header file
#include "HuffmanNode.h"

using namespace std;

HuffmanNode::HuffmanNode() = default;

HuffmanNode::HuffmanNode(int data_in) : data{ data_in } {  }

ostream& operator<<(ostream & out, const HuffmanNode& node) {
	if(&node != nullptr && node.data != 0)
		out << "\t" << node.data;
	out << "\n";
	out << *(node.left);
	out << *(node.right);

	return out;
}