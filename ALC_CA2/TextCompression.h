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

	static string encode_as_string_of_binary_from_map(const string& input, const map<char, string>& char_encoding);
	static void populate_char_frequency(const string& input, map<char, int>& char_frequency);
	static map<char, string> get_char_mapping_from_tree(HuffmanTree* huffman_tree, map<char, int> char_frequency);
	static HuffmanTree* get_huffman_tree_from_map(map<char, int> char_frequency);
	static priority_queue<HuffmanTree*, vector<HuffmanTree*>, CompareHuffmanTree> get_priority_queue_from_map(map<char, int> char_frequency);
public:
	static string encode_as_string_of_binary(const string& input, ofstream& out_file);
};