#include "TextCompression.h"

TextCompression::TextCompression() = default;

string TextCompression::encode(const string & input, ofstream & out_file) {
	map<char, int> char_frequency = get_char_frequency(input);

	map<char, int>::iterator it = char_frequency.begin();
	while (it != char_frequency.end()) {
		std::cout << it->first << "\t" << it->second << "\n";
		it++;
	}

	return "";
}

map<char, int> TextCompression::get_char_frequency(const string & input) {
	map<char, int> char_frequency;

	for (char current_char : input) {
		if (char_frequency.find(current_char) == char_frequency.end())
			char_frequency.insert(pair<char, int>(current_char, 1));
		else
			char_frequency[current_char]++;
	}

	return char_frequency;
}