#include "TextCompression.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {

	ofstream encoded = ofstream("encoded.txt");
	ofstream decoded = ofstream("decoded.txt");
	HuffmanTree* huffman_tree;

	string plain_text = "Eerie eyes seen near lake.";

	string encoded_text = TextCompression::encode_input_text(plain_text, encoded, huffman_tree);
	string decoded_text = TextCompression::decode_input_text(encoded_text, decoded, huffman_tree);

	return 0;
}
