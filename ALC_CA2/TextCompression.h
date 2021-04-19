#pragma once

#include "HuffmanTree.h"
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class TextCompression
{
private:
	TextCompression();

	static const int PSEUDO_EOF = 256;

	static string encode_input_text(const string& input, HuffmanTree*& huffman_tree_out);
	static string encode_from_char_mapping(const string& input, const map<int, string>& char_encoding);
	static map<int, string> get_char_mapping_from_tree(HuffmanTree* huffman_tree, map<int, int> char_frequency);
	static HuffmanTree* get_huffman_tree_from_map(map<int, int> char_frequency);
	static priority_queue<HuffmanTree*, vector<HuffmanTree*>, CompareHuffmanTree> get_priority_queue_from_map(map<int, int> char_frequency);
	static void populate_char_frequency(const string& input, map<int, int>& char_frequency);

	static string decode_input_text(const string& input, const HuffmanTree* huffman_tree);
	
	static void get_string_from_file(ifstream& in_file, string& out);

	static void get_compressed_string(string& encoded_string, string& compressed_string_out);
	static void pad_string_with_zeros(string& to_pad);

	static void get_binary_string(const string& encoded_string, string& binary_string_out);

	static string encode_huffman_tree(HuffmanTree* huffman_tree);
	static string encode_huffman_tree_helper(HuffmanTree* huffman_tree, string& accumulated_string);

public:
	static string encode_input_text_to_file(const string& input, ofstream& out_file, HuffmanTree*& huffman_tree_out);						// Section A - task 4
	static HuffmanTree* encode_input_file_to_file(ifstream& in_file, ofstream& out_file);

	static string decode_input_text_to_file(const string& input, ofstream& out_file, const HuffmanTree* huffman_tree);						// Section A - task 5
	static void decode_input_file_to_file(ifstream& in_file, ofstream& out_file, const HuffmanTree* huffman_tree);
	
	static HuffmanTree* compress_input_file(ifstream& in_file, ofstream& out_file);
	static void decompress_input_file(ifstream& in_file, ofstream& out_file, const HuffmanTree* huffman_tree);
	
	static void compress_input_file_independent(ifstream& in_file, ofstream& out_file);
	static void decompress_input_file_independent(ifstream& in_file, ofstream& out_file);
};
