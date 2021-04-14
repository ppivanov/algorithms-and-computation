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
}

string HuffmanTree::get_path_to_char(char to_find)
{
	return get_path_to_char(to_find, root, "");
}

string HuffmanTree::get_path_to_char(char to_find, HuffmanNode* node, string path)
{
	if (node == nullptr || node->data == to_find)
		return path;

	if (node->left != nullptr) {
		path.push_back('0');																// add a 0 to the vector before moving to the left side of the tree
		string returned_path = get_path_to_char(to_find, node->left->root, path);
		if (returned_path != "") 
			return returned_path;
		
		path.pop_back();																	// remove the 0 since it has already been visited
	}

	if (node->right != nullptr) {
		path.push_back('1');																// add a 1 to the vector before moving to the right side
		string returned_path = get_path_to_char(to_find, node->right->root, path);
		if (returned_path != "")
			return returned_path;
	}

	return "";																				// return an empty string if there wasn't a match
}

bool CompareHuffmanTree::operator() (const HuffmanTree* lhs, const HuffmanTree* rhs) const
{
	return lhs->weight > rhs->weight;
}

ostream& operator<<(ostream& out, const HuffmanTree& tree) {
	if ( &tree != nullptr && tree.root != nullptr) {
		out << tree.weight;
		out << *tree.root;
	}

	return out;
}

