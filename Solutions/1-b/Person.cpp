#include <iostream>
#include "Person.h"

Person::Person(const string& nameIn) : name{nameIn} {}

Person::~Person() = default;

bool Person::operator<(const Person& person) const {
	//return (name < person.name);
	return name.compare(person.name) < 0;
}
