#include <iostream>
#include "BinarySearchTree.h"
#include <fstream>
#include <random>

int main() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 30);

    ofstream outFile("bst.txt");
    ifstream inFile("bst.txt");

    BinarySearchTree bst = BinarySearchTree();
    
    bst.add(15);
    for (int i = 0; i < 20; i++) {
		bst.add(distribution(generator));
    }
    
    std::cout << "Tree before serializing:\n";
    bst.pretty_print();
    bst.Serialise(outFile);
    bst.destruct_tree();

    std::cout << "\n\nTree after deserializing file:\n";
    bst.Deserialise(inFile);
    bst.pretty_print();

    return 0;
}