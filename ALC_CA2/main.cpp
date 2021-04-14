#include "TextCompression.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {

	ofstream temp = ofstream("a.txt");
	TextCompression::encode_as_string_of_binary("Eerie eyes seen near lake.", temp);

	return 0;
}
