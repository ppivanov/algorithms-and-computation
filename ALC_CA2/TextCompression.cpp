#include "TextCompression.h"
#include <sstream>
#include <bitset>

using namespace std;

TextCompression::TextCompression() = default;


// Private functions

string TextCompression::encode_input_text(const string& input, HuffmanTree*& huffman_tree_out) {
	if (input.length() < 2)																								// shortcut execution and return the input string. No point encoding it.
		return input;

	map<int, int> char_frequency;
	populate_char_frequency(input, char_frequency);

	huffman_tree_out = get_huffman_tree_from_map(char_frequency);
	//cout << *huffman_tree_out << "\n\n";

	map<int, string> char_encoding = get_char_mapping_from_tree(huffman_tree_out, char_frequency);						// This line warns about a memory leak in the function, still, nothing is being created nor detatched
	string encoded_string = encode_from_char_mapping(input, char_encoding);

	return encoded_string;
}

string TextCompression::encode_from_char_mapping(const string& input, const map<int, string>& char_encoding) {
	string encoded_string = "";
	for (int input_char : input) {
		encoded_string.append(char_encoding.at(input_char));
	}
	encoded_string.append(char_encoding.at(PSEUDO_EOF));																// Append the EOF character at the very end
	return encoded_string;
}

map<int, string> TextCompression::get_char_mapping_from_tree(HuffmanTree* huffman_tree, map<int, int> char_frequency) {
	map<int, string> char_path;

	for (pair<int, int> char_pair : char_frequency) {
		string path_to_char = huffman_tree->get_path_to_char(char_pair.first);

		char_path.insert(pair<int, string>(char_pair.first, path_to_char));
		cout << (char)char_pair.first << "\t" << char_pair.first << "\t" << path_to_char << "\n";
	}

	return char_path;
}

HuffmanTree* TextCompression::get_huffman_tree_from_map(map<int, int> char_frequency)
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
	TextCompression::get_priority_queue_from_map(map<int, int> char_frequency) {
		priority_queue<HuffmanTree*, vector<HuffmanTree*>, CompareHuffmanTree> tree_queue;

		map<int, int>::iterator it = char_frequency.begin();											// Transferring the map elements to a priority queue
		while (it != char_frequency.end()) {
			tree_queue.push(new HuffmanTree(it->first, it->second));
			++it;
		}

		return tree_queue;
}

void TextCompression::populate_char_frequency(const string& input, map<int, int>& char_frequency) {
	char_frequency.insert(pair<int, int>(PSEUDO_EOF, 1));																// Pseudo EOF character
	for (char current_char : input) {
		if (char_frequency.find(current_char) == char_frequency.end())
			char_frequency.insert(pair<int, int>(current_char, 1));
		else
			char_frequency[current_char]++;
	}
}

string TextCompression::decode_input_text(const string& input, const HuffmanTree* huffman_tree) {
	string decoded_string = "";
	string traversed = "";
	HuffmanTree traversal_copy = *huffman_tree;
	for (int i = 0; i <= input.size(); ++i) {
		if (traversal_copy.root->data == PSEUDO_EOF)
			break;
		if (traversal_copy.root->data != 0) {																			// There is a char at this position. Add it to the string and reset the path.
			decoded_string.push_back(traversal_copy.root->data);
			traversal_copy = *huffman_tree;
			--i;																										// Required in order to decode the last character
		}
		else if (i != input.size()) {
			if (input[i] == '0') {
				traversed += '0';
				traversal_copy = *(traversal_copy.root->left);
			}
			else {
				traversed += '1';
				traversal_copy = *(traversal_copy.root->right);
			}
		}
	}

	return decoded_string;
}

void TextCompression::get_string_from_file(ifstream& in_file, string& out)
{
	/***************************************************************************************
	*    Usage: Used
	*    Title: Read whole ASCII file into C++ std::string [duplicate]
	*    Author: McHenry, T [StackOverflow] (editted by resueman [StackOverflow])
	*	 Date posted: 8 April 2010
	*	 Type: Source code
	*    Availability: https://stackoverflow.com/a/2602060
	*    Accessed on: 15 April 2021
	*
	***************************************************************************************/

	in_file.seekg(0, std::ios::end);
	out.reserve(in_file.tellg());
	in_file.seekg(0, std::ios::beg);

	out.assign((std::istreambuf_iterator<char>(in_file)),
		std::istreambuf_iterator<char>());
}

void TextCompression::get_compressed_string(string& encoded_string, string& compressed_string_out) {
	pad_string_with_zeros(encoded_string);

	/***************************************************************************************
	*    Usage: Used
	*    Title: Convert a string of binary into an ASCII string (C++)
	*    Author: Wilson, D. [StackOverflow]
	*	 Date posted: 28 April 2014
	*	 Type: Source code
	*    Availability: https://stackoverflow.com/a/23344876
	*    Accessed on: 15 April 2021
	*
	***************************************************************************************/

	compressed_string_out = "";
	istringstream encoded_stream(encoded_string);
	string output;
	while (encoded_stream.good())
	{
		bitset<8> bit_set;
		encoded_stream >> bit_set;
		char bits_as_char = char(bit_set.to_ulong());																	// Casting the bitset to a character
		compressed_string_out.push_back(bits_as_char);
	}
}

void TextCompression::pad_string_with_zeros(string& to_pad) {
	int number_bits = to_pad.size();
	int number_bits_required = number_bits + 8 - (number_bits % 8);
	int num_pads = number_bits_required - number_bits;

	for (int i = 0; i < num_pads; i++) {
		to_pad.push_back('0');
	}
}

void TextCompression::get_binary_string(const string& encoded_string, string& binary_string_out) {
	binary_string_out = "";
	for (char encoded_char : encoded_string) {
		/***************************************************************************************
		*    Usage: Used
		*    Title: Converting chars to binary in C++ [duplicate]
		*    Author: <username contains non-unicode characters> [StackOverflow]
		*	 Date posted: 12 September 2015
		*	 Type: Source code
		*    Availability: https://stackoverflow.com/a/32538948
		*    Accessed on: 18 April 2021
		*
		***************************************************************************************/

		binary_string_out.append(bitset<8>(encoded_char).to_string());
	}
}


// Public functions

string TextCompression::encode_input_text_to_file(const string& input, ofstream& out_file, HuffmanTree*& huffman_tree_out) {
	string encoded_string = encode_input_text(input, huffman_tree_out);
	out_file << encoded_string;

	return encoded_string;
}

HuffmanTree* TextCompression::encode_input_file_to_file(ifstream& in_file, ofstream& out_file) {
	HuffmanTree* huffman_tree;
	string input_text;
	get_string_from_file(in_file, input_text);

	string encoded_string = encode_input_text_to_file(input_text, out_file, huffman_tree);

	return huffman_tree;
}


string TextCompression::decode_input_text_to_file(const string& input, ofstream& out_file, const HuffmanTree* huffman_tree) {
	string decoded_string = decode_input_text(input, huffman_tree);
	out_file << decoded_string;

	return decoded_string;
}

void TextCompression::decode_input_file_to_file(ifstream& in_file, ofstream& out_file, const HuffmanTree* huffman_tree) {
	string input_text;
	get_string_from_file(in_file, input_text);

	string decoded_string = decode_input_text_to_file(input_text, out_file, huffman_tree);

	//cout << decoded_string << endl;
}


HuffmanTree* TextCompression::compress_input_file(ifstream& in_file, ofstream& out_file) {
	HuffmanTree* huffman_tree_out;
	string input_text;
	get_string_from_file(in_file, input_text);

	string encoded_string = encode_input_text(input_text, huffman_tree_out);								// false-positive warning for memory leak

	string compressed_string_out;
	get_compressed_string(encoded_string, compressed_string_out);

	out_file << compressed_string_out;

	return huffman_tree_out;
}

void TextCompression::decompress_input_file(ifstream& in_file, ofstream& out_file, const HuffmanTree* huffman_tree) {
	string input_text;
	get_string_from_file(in_file, input_text);

	string binary_string_out;
	get_binary_string(input_text, binary_string_out);

	string decoded_string = decode_input_text_to_file(binary_string_out, out_file, huffman_tree);

	cout << decoded_string << endl;
}
