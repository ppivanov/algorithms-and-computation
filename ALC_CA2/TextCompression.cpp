#include "TextCompression.h"
#include <queue>
#include <vector>
#include "HuffmanTree.h"

using std::priority_queue;

TextCompression::TextCompression() = default;

string TextCompression::encode(const string & input, ofstream &out_file) {
	map<char, int> char_frequency;
	priority_queue<HuffmanTree> tree_queue;
	
	fill_char_frequency(input, char_frequency);

	map<char, int>::iterator it = char_frequency.begin();									// Transferring the map elements to a priority queue
	while (it != char_frequency.end()) {
		tree_queue.push(HuffmanTree(it->first, it->second));
		it++;
	}

	while (!tree_queue.empty()) {															// Print the contents of the priority queue
		std::cout << tree_queue.top().weight << "\n";
		tree_queue.pop();
	}

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