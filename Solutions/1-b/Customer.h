#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"

class Customer : public Person
{
public:
	Customer(const string& name);
	~Customer();

	void printname();
private:
};


#endif // !CUSTOMER_H
