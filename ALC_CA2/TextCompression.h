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

	static string encode_from_char_mapping(const string& input, const map<char, string>& char_encoding);
	static void populate_char_frequency(const string& input, map<char, int>& char_frequency);
	static map<char, string> get_char_mapping_from_tree(HuffmanTree* huffman_tree, map<char, int> char_frequency);
	static HuffmanTree* get_huffman_tree_from_map(map<char, int> char_frequency);
	static priority_queue<HuffmanTree*, vector<HuffmanTree*>, CompareHuffmanTree> get_priority_queue_from_map(map<char, int> char_frequency);
public:
	static string encode_input_text(const string& input, ofstream& out_file, HuffmanTree*& huffman_tree_out);						// Section A - task 4
	static string decode_input_text(const string& input, ofstream& out_file, const HuffmanTree* huffman_tree);						// Section A - task 5
};