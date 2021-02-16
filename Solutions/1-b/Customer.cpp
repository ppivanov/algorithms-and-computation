#include <iostream>
#include "Customer.h"

Customer::Customer(const string& nameIn) : Person(nameIn) {}

Customer::~Customer() = default;

void Customer::printname() {
	std::cout << name << " wishes to file a complaint." << endl;
}
