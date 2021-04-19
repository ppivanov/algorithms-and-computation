#include "TextCompression.h"
#include <sstream>
#include <bitset>
#include <stack>

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
		//cout << (char)char_pair.first << "\t" << char_pair.first << "\t" << path_to_char << "\n";
	}

	return char_path;
}

HuffmanTree* TextCompression::get_huffman_tree_from_map(map<int, int> char_frequency)
{
	auto tree_queue = get_priority_queue_from_map(char_frequency);														// using auto to detect the type as it's too long and hard to read

	while (tree_queue.size() > 2) {																						// While there are more than 2 elements in the queue pop the fist two and add them to a new tree
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

		map<int, int>::iterator it = char_frequency.begin();															// Transferring the map elements to a priority queue
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
	for (size_t i = 0; i <= input.size(); ++i) {
		if (traversal_copy.root->data == PSEUDO_EOF)
			break;
		if (traversal_copy.root->data != 0) {																			// There is a char at this position. Add it to the string and reset the path.
			decoded_string.push_back((char)traversal_copy.root->data);
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
		*    Author: <username contains unicode characters that cannot be used in this file> [StackOverflow]
		*	 Date posted: 12 September 2015
		*	 Type: Source code
		*    Availability: https://stackoverflow.com/a/32538948
		*    Accessed on: 18 April 2021
		*
		***************************************************************************************/

		binary_string_out.append(bitset<8>(encoded_char).to_string());
	}
}

// ref: https://engineering.purdue.edu/ece264/17au/hw/HW13?alt=huffman
string TextCompression::encode_huffman_tree(HuffmanTree* huffman_tree) {
	string encoded_string = "";
	encode_huffman_tree_helper(huffman_tree, encoded_string);
	encoded_string.append("0");
	return encoded_string;
}

string TextCompression::encode_huffman_tree_helper(HuffmanTree* huffman_tree, string& accumulated_string) {
	if (huffman_tree != nullptr) {
		encode_huffman_tree_helper(huffman_tree->root->left, accumulated_string);
		encode_huffman_tree_helper(huffman_tree->root->right, accumulated_string);
		if (huffman_tree->root->data != 0)
			accumulated_string.append("1" + bitset<8>(huffman_tree->root->data).to_string());
		else
			accumulated_string.append("0");
	}

	return accumulated_string;
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

	string encoded_string = encode_input_text(input_text, huffman_tree_out);											// false-positive warning for memory leak

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

	//cout << decoded_string << endl;
}


void TextCompression::compress_input_file_independent(ifstream& in_file, ofstream& out_file) {
	HuffmanTree* huffman_tree_out;
	string input_text;
	get_string_from_file(in_file, input_text);

	string encoded_string = encode_input_text(input_text, huffman_tree_out);											// false-positive warning for memory leak

	string encoded_tree = encode_huffman_tree(huffman_tree_out);
	pad_string_with_zeros(encoded_tree);
	string encoded_tree_size = bitset<32>(encoded_tree.size() / 8).to_string();

	encoded_string = encoded_tree_size + encoded_tree + encoded_string;

	string compressed_string_out;
	get_compressed_string(encoded_string, compressed_string_out);

	out_file << compressed_string_out;
}

void TextCompression::decompress_input_file_independent(ifstream& in_file, ofstream& out_file) {
	string input_text;
	get_string_from_file(in_file, input_text);

	string binary_string_out;
	get_binary_string(input_text, binary_string_out);

	bitset<32> bit_set;
	stringstream ss_tree_size(binary_string_out.substr(0, 32));
	ss_tree_size >> bit_set;
	unsigned int bits_used_for_tree = bit_set.to_ulong() * 8;

	string encoded_string = binary_string_out.substr(bits_used_for_tree + 32, binary_string_out.size() - (bits_used_for_tree + 32));
	string encoded_tree = binary_string_out.substr(32, bits_used_for_tree);

	stack<HuffmanTree*> stack;
	HuffmanTree* huffman_tree = nullptr;
	bool eof_added = false;
	for (unsigned int i = 0; i <= bits_used_for_tree;) {
		unsigned int position = i;
		if (bits_used_for_tree - position > 8) {
			if (encoded_tree[position] == '1') {												// if true, next char is a leaf node
				bitset<8> char_bit_set;
				stringstream ss_tree_size(encoded_tree.substr(position + 1, 8));
				ss_tree_size >> char_bit_set;
				int to_add = char_bit_set.to_ulong();
				if (eof_added == false && char_bit_set.to_string() == "00000000") {
					eof_added = true;
					to_add = PSEUDO_EOF;
				}
				stack.push(new HuffmanTree(to_add, 0));
				i += 9;
				continue;
			}
			/*else if (stack.size() == 1) {
				huffman_tree = stack.top();
				break;
			}*/
			else if (stack.size() > 1) {
				HuffmanTree* first_pop = stack.top();
				stack.pop();

				HuffmanTree* second_pop = stack.top();
				stack.pop();

				stack.push(new HuffmanTree(second_pop, first_pop, 0));
			}
			++i;
		}
		else break;								
	}
	if (huffman_tree == nullptr) {																	// restack the trees until a single one is left
		while (stack.size() > 1) {
			HuffmanTree* first_pop = stack.top();
			stack.pop();

			HuffmanTree* second_pop = stack.top();
			stack.pop();

			stack.push(new HuffmanTree(second_pop, first_pop, 0));
		}

		huffman_tree = stack.top();
		cout << *huffman_tree;
	}

	// To construct a Huffman coding tree from the header information, we make use of a stack.
	// When a 1 is read, we read the next byte and push the corresponding ASCII character onto the stack.
	// When a 0 (bit or character) is read, if the stack contains only one element, we have constructed 
	// the entire Huffman coding tree.Otherwise, there must be more than one element in the stack.We create
	// a new node, and pop the top two elements off the stack.We make the first element off the stack 
	// the right child of the new node, and the second element off the stack the left child of the new
	// node. After that, we push the newly created node onto the stack.

	string decoded_string = decode_input_text_to_file(encoded_string, out_file, huffman_tree);

	//cout << decoded_string << endl;
}
