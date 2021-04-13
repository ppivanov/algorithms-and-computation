// Pavel Ivanov x00149863

#include <fstream>
#include <iostream>
#include <string>

using std::ifstream;
using std::ofstream;
using std::ostream;

class TreeNode
{
private:
	int data = 0;
	TreeNode* left;
	TreeNode* right;

	friend class BinarySearchTree;
public:
	TreeNode(int data);
};
TreeNode::TreeNode(int data) : data{ data } {  };


class BinarySearchTree																	// we were asked to create
{
private:
	TreeNode* root = nullptr;

	void add(TreeNode* toAdd, TreeNode* attachHere);
	int serialise(ofstream& fp, TreeNode* root);
	void destruct_tree();
	void destruct_tree(TreeNode* node);
	void print(ostream& outStream, TreeNode* node);
public:
	BinarySearchTree();
	~BinarySearchTree();
	TreeNode* deSerialise(ifstream& inFile);
	void add(int);
	int Serialise(ofstream& outFile);

	void print(ostream& outStream);
};
ostream& operator<<(ostream& outStream, BinarySearchTree& bst) {
	bst.print(outStream);
	return outStream;
}

BinarySearchTree::BinarySearchTree() = default;

BinarySearchTree::~BinarySearchTree() {
	destruct_tree();
}

void BinarySearchTree::destruct_tree() {
	destruct_tree(root);
	root = nullptr;
}

void BinarySearchTree::destruct_tree(TreeNode* node) {
	if (node != nullptr) {
		destruct_tree(node->left);
		destruct_tree(node->right);
		delete node;
		node = nullptr;
	}
}
void BinarySearchTree::print(ostream& outStream) {
	print(outStream, root);
}
void BinarySearchTree::print(ostream& outStream, TreeNode* node) {
	if (node != nullptr) {
		outStream << node->data << "\t";
		print(outStream, node->left);
		print(outStream, node->right);
	}
}

/***************************************************************************************

*    Usage: Used
*    Title: Serialize/Deserialize Binary Tree
*    Author: Educative, Inc
*    Date: 2021
*    Code version: N/A
*    Availability: https://www.educative.io/m/serialize-deserialize-binary-tree
*
***************************************************************************************/
TreeNode* BinarySearchTree::deSerialise(ifstream& inFile) {										// nope
	if (inFile.eof()) {
		return nullptr;
	}
	int val;
	inFile.read((char*)&val, sizeof(val));
	if (val == INT_MIN) {
		return nullptr;
	}

	TreeNode* pNode = new TreeNode(val);
	pNode->left = deSerialise(inFile);
	pNode->right = deSerialise(inFile);

	root = pNode;
	return pNode;
}

void BinarySearchTree::add(int nodeData) {
	TreeNode* toAdd = new TreeNode(nodeData);
	if (root == nullptr)
		root = toAdd;
	else
		add(toAdd, root);
}

void BinarySearchTree::add(TreeNode* toAdd, TreeNode* attachHere) {
	if (attachHere->data > toAdd->data) {
		if (attachHere->left == nullptr)
			attachHere->left = toAdd;
		else
			add(toAdd, attachHere->left);
	}
	else if (attachHere->data < toAdd->data) {
		if (attachHere->right == nullptr)
			attachHere->right = toAdd;
		else 
			add(toAdd, attachHere->right);
	}
}

int BinarySearchTree::Serialise(ofstream& outFile) {
	int result = serialise(outFile, root);
	outFile << "\n";
	outFile.close();

	return result;
}
int BinarySearchTree::serialise(ofstream& fp, TreeNode* node) {
	if (fp.is_open()) {
		if (node == nullptr) return 1;

		fp << node->data << "\n";
		serialise(fp, node->left);
		serialise(fp, node->right);
	}
	else {
		return -1;
	}
}



int main() {

	BinarySearchTree bst = BinarySearchTree();

	bst.add(16);
	bst.add(6);
	bst.add(5);
	bst.add(9);
	bst.add(10);
	bst.add(19);
	bst.add(21);
	bst.add(14);
	bst.add(23);
	bst.add(8);

	ofstream outFile("bst.txt");
	bst.Serialise(outFile);

	std::cout << bst << std::endl;

	BinarySearchTree dsTest = BinarySearchTree();
	ifstream inFile("bst.txt");
	bst.deSerialise(inFile);

	std::cout << dsTest << std::endl;

	return 0;
}