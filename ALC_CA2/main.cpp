#include <fstream>
#include <iostream>
#include "TextCompression.h"

using std::ofstream;

int main() {

	ofstream temp = ofstream("a.txt");
	//TextCompression::encode("Eerie eyes seen near lake.", temp);
	TextCompression::encode("E", temp);

	return 0;
}
