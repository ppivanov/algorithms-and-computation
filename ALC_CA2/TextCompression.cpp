#include "TextCompression.h"

using namespace std;

TextCompression::TextCompression() = default;

string TextCompression::encode_as_string_of_binary(const string& input, ofstream& out_file) {
	if (input.length() < 2) {																			// shortcut execution and return the input string. No point encoding it.
		return input;
	}

	map<char, int> char_frequency;
	populate_char_frequency(input, char_frequency);

	HuffmanTree* huffman_tree = get_huffman_tree_from_map(char_frequency);
	//cout << *huffman_tree << "\n\n";

	map<char, string> char_encoding = get_char_mapping_from_tree(huffman_tree, char_frequency);			// This line warns about a memory leak in the function, still, nothing is being created nor detatched

	string input_as_1_0_string = encode_as_string_of_binary_from_map(input, char_encoding);
	out_file << input_as_1_0_string;

	return input_as_1_0_string;
}

void TextCompression::populate_char_frequency(const string &input, map<char, int>& char_frequency) {
	for (char current_char : input) {
		if (char_frequency.find(current_char) == char_frequency.end())
			char_frequency.insert(pair<char, int>(current_char, 1));
		else
			char_frequency[current_char]++;
	}
}

HuffmanTree* TextCompression::get_huffman_tree_from_map(map<char, int> char_frequency)
{
	auto tree_queue = get_priority_queue_from_map(char_frequency);										// using auto to detect the type as it's too long and hard to read

	while (tree_queue.size() > 2) {																		// While there are more than 2 elements in the queue pop the fist two and add them to a new tree
		HuffmanTree* first_pop = tree_queue.top();
		tree_queue.pop();

		HuffmanTree* second_pop = tree_queue.top();
		tree_queue.pop();

		tree_queue.push(new HuffmanTree(first_pop, second_pop, first_pop->weight + second_pop->weight));
	}

	HuffmanTree* first_pop = tree_queue.top();
	tree_queue.pop();

	HuffmanTree* second_pop = tree_queue.top();
	tree_queue.pop();

	HuffmanTree* final_tree = new HuffmanTree(first_pop, second_pop, first_pop->weight + second_pop->weight);

	return final_tree;
}

priority_queue<HuffmanTree*, vector<HuffmanTree*>, CompareHuffmanTree> 
	TextCompression::get_priority_queue_from_map(map<char, int> char_frequency) {
		priority_queue<HuffmanTree*, vector<HuffmanTree*>, CompareHuffmanTree> tree_queue;

		map<char, int>::iterator it = char_frequency.begin();											// Transferring the map elements to a priority queue
		while (it != char_frequency.end()) {
			tree_queue.push(new HuffmanTree(it->first, it->second));
			it++;
		}
	
		return tree_queue;
}

map<char, string> TextCompression::get_char_mapping_from_tree(HuffmanTree* huffman_tree, map<char, int> char_frequency) {
	map<char, string> char_path;

	for (pair<char, int> char_pair : char_frequency) {
		string path_to_char = huffman_tree->get_path_to_char(char_pair.first);

		char_path.insert(pair<char, string>(char_pair.first, path_to_char));
		cout << char_pair.first << "\t" << path_to_char << "\n";
	}

	return char_path;
}

string TextCompression::encode_as_string_of_binary_from_map(const string& input, const map<char, string>& char_encoding) {
	string encoded_string = "";
	for (char input_char : input) {
		encoded_string.append(char_encoding.at(input_char));
	}

	return encoded_string;
}