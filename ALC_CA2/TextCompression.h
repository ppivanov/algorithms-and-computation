#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>

using std::map;
using std::ofstream;
using std::pair;
using std::string;

class TextCompression
{
public:
	static string encode(const string& input, ofstream& out_file);

private:
	TextCompression();

	static map<char, int> get_char_frequency(const string &input);
};