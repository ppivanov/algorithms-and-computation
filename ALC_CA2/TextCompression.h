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
	static void fill_char_frequency(const string& input, map<char, int>& char_frequency);
	static priority_queue<HuffmanTree*, vector<HuffmanTree*>, CompareHuffmanTree> get_priority_queue_from_map(map<char, int> char_frequency);
	static HuffmanTree* get_huffman_tree_from_map(map<char, int> char_frequency);
public:
	static string encode(const string& input, ofstream& out_file);
};