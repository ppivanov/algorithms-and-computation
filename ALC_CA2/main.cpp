#include "TextCompression.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {

	HuffmanTree* huffman_tree;

	/*string plain_text = "Eerie eyes seen near lake.";

	string encoded_text = TextCompression::encode_input_text(plain_text, encoded, huffman_tree);
	string decoded_text = TextCompression::decode_input_text(encoded_text, decoded, huffman_tree);*/

	ifstream initial_in("initial.txt");
	ofstream encoded_out("encoded.txt");

	huffman_tree = TextCompression::encode_input_file_to_file(initial_in, encoded_out);

	initial_in.close();
	encoded_out.close();



	ifstream encoded_in("encoded.txt");
	ofstream decoded_out("decoded.txt");

	TextCompression::decode_input_file_to_file(encoded_in, decoded_out, huffman_tree);

	encoded_in.close();
	decoded_out.close();



	initial_in.open("initial.txt");
	ofstream compressed_out("compressed.txt");

	TextCompression::compress_input_file(initial_in, compressed_out);

	initial_in.close();
	compressed_out.close();

	return 0;
}
