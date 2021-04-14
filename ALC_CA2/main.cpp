#include "TextCompression.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {

	ofstream temp = ofstream("a.txt");
	TextCompression::encode("Eerie eyes seen near lake.", temp);

	return 0;
}
