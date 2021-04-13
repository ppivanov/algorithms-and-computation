#include <fstream>
#include <iostream>
#include <map>
#include <string>

using std::map;
using std::ofstream;
using std::pair;
using std::string;

string encode(const string &input, ofstream &out_file);

int main() {

	ofstream temp = ofstream("a.txt");
	encode("Eerie eyes seen near lake.", temp);

	return 0;
}


string encode(const string &input, ofstream &out_file) {
	map<char, int> char_frequency;

	for (char current_char : input) {
		if (char_frequency.find(current_char) == char_frequency.end())
			char_frequency.insert(pair<char, int>(current_char, 1));
		else
			char_frequency[current_char]++;
	}

	map<char, int>::iterator it = char_frequency.begin();
	while (it != char_frequency.end()) {
		std::cout << it->first << "\t" << it->second << "\n";
		it++;
	}

	return "";
}