#include "TextCompression.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {

	HuffmanTree* huffman_tree;

	//string plain_text = "Eerie eyes seen near lake.";

	//string encoded_text = TextCompression::encode_input_text(plain_text, encoded, huffman_tree);
	//string decoded_text = TextCompression::decode_input_text(encoded_text, decoded, huffman_tree);



	ifstream initial_in("initial.txt", ios::binary);																// Opening all files in binary mode to read the full contents.
	ofstream encoded_out("encoded.txt", ios::binary);																
	huffman_tree = TextCompression::encode_input_file_to_file(initial_in, encoded_out);								// write the encoded string as 1s and 0s to the file
	initial_in.close();
	encoded_out.close();
																													/***************************************************************************************
																													 *    Usage : Used
																													 *    Title : using fstream to read every character including spaces and newline
																													 *    Author : luke [StackOverflow]
																													 *    Date posted : 22 September 2008
																													 *    Type : Source code
																													 *    Availability : https://stackoverflow.com/a/117015	
																													 *    Accessed on : 19 April 2021
																													 *
																													***************************************************************************************/


	ifstream encoded_in("encoded.txt", ios::binary);
	ofstream decoded_out("decoded.txt", ios::binary);
	TextCompression::decode_input_file_to_file(encoded_in, decoded_out, huffman_tree);								// decode the 1s and 0s and restore the original text
	encoded_in.close();
	decoded_out.close();



	initial_in.open("initial.txt", ios::binary);
	ofstream compressed_out("compressed.txt", ios::binary);
	huffman_tree = nullptr;
	huffman_tree = TextCompression::compress_input_file(initial_in, compressed_out);								// compress the file and return the Huffman tree
	initial_in.close();
	compressed_out.close();



	ifstream compressed_in("compressed.txt", ios::binary);
	ofstream decompressed_out("decompressed.txt", ios::binary);
	TextCompression::decompress_input_file(compressed_in, decompressed_out, huffman_tree);							// use the Huffman tree to decompress the file
	compressed_in.close();
	decompressed_out.close();



	initial_in.open("initial.txt", ios::binary);
	ofstream independent_compressed_out("independent-compressed.txt", ios::binary);
	TextCompression::compress_input_file_independent(initial_in, independent_compressed_out);						// compress the file and save the Tree in the first bytes
	initial_in.close();
	independent_compressed_out.close();


	ifstream independent_compressed_in("independent-compressed.txt", ios::binary);
	ofstream independent_decompressed_out("independent-decompressed.txt", ios::binary);
	TextCompression::decompress_input_file_independent(independent_compressed_in, independent_decompressed_out);	// decode the tree from the first bytes and decompress the contents
	independent_compressed_in.close();
	independent_decompressed_out.close();



	initial_in.open("initial-2.txt", ios::binary);
	independent_compressed_out.open("independent-compressed-2.txt", ios::binary);
	TextCompression::compress_input_file_independent(initial_in, independent_compressed_out);						// testing with a slightly bigger file
	initial_in.close();
	independent_compressed_out.close();


	independent_compressed_in.open("independent-compressed-2.txt", ios::binary);
	independent_decompressed_out.open("independent-decompressed-2.txt", ios::binary);
	TextCompression::decompress_input_file_independent(independent_compressed_in, independent_decompressed_out);	// testing with a slightly bigger file
	independent_compressed_in.close();
	independent_decompressed_out.close();

	return 0;
}
