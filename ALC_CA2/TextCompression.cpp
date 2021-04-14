#include "TextCompression.h"

using namespace std;

TextCompression::TextCompression() = default;

string TextCompression::encode(const string& input, ofstream& out_file) {
	if (input.length() < 2) {																// shortcut execution and return the input string. No point encoding it.
		return input;
	}

	map<char, int> char_frequency;
	fill_char_frequency(input, char_frequency);

	HuffmanTree* huffman_tree = get_huffman_tree_from_map(char_frequency);

	return "";
}

void TextCompression::fill_char_frequency(const string &input, map<char, int>& char_frequency) {
	for (char current_char : input) {
		if (char_frequency.find(current_char) == char_frequency.end())
			char_frequency.insert(pair<char, int>(current_char, 1));
		else
			char_frequency[current_char]++;
	}
}

HuffmanTree* TextCompression::get_huffman_tree_from_map(map<char, int> char_frequency)
{
	auto tree_queue = get_priority_queue_from_map(char_frequency);

	while (tree_queue.size() > 2) {															// While there are more than 2 elements in the queue pop the fist two and add them to a new tree
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
	std::cout << *final_tree;

	return final_tree;
}

priority_queue<HuffmanTree*, vector<HuffmanTree*>, CompareHuffmanTree> TextCompression::get_priority_queue_from_map(map<char, int> char_frequency)
{
		priority_queue<HuffmanTree*, vector<HuffmanTree*>, CompareHuffmanTree> tree_queue;
	
		map<char, int>::iterator it = char_frequency.begin();									// Transferring the map elements to a priority queue
		while (it != char_frequency.end()) {
			tree_queue.push(new HuffmanTree(it->first, it->second));
			it++;
		}
	
		return tree_queue;
}
