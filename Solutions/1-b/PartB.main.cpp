#include <iostream>
#include <algorithm>
#include <vector>
#include "Person.h"
#include "Employee.h"
#include "Customer.h"

using namespace std;

bool comparePersonPtrs(const Person* lhs, const Person* rhs) {
	return *lhs < *rhs;
}

int main()
{
	Person* p1 = new Employee("Alfie", 200);
	Person* p2 = new Customer("Zeddy");
	Person* p3 = new Customer("Bethany");
	Person* p4 = new Employee("Joe", 200);
	Person* p5 = new Employee("Mama", 200);

	vector<Person*> v = { p1, p2, p3, p4, p5 };

	sort(v.begin(), v.end(), comparePersonPtrs);

	for (Person* p : v)
	{
		p->printname();
	}

	return 0;
}
