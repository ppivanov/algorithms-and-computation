#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {
public: 
	Person(const string& name);
	~Person();
	
	virtual void printname() = 0;
	bool operator<(const Person& person) const;
protected: 
	string name; 
};

#endif
