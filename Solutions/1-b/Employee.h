#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"

class Employee : public Person
{
public:
	Employee(const string& name, const double& salary);
	~Employee();

	void printname();
private:
	double salary;
};


#endif // !EMPLOYEE_H
