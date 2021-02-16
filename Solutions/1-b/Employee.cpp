#include <iostream>
#include "Employee.h"

Employee::Employee(const string& nameIn, const double& salaryIn) : Person(nameIn), salary{salaryIn} {}

Employee::~Employee() = default;

void Employee::printname() {
	std::cout << name << " : " << salary << endl;
}
