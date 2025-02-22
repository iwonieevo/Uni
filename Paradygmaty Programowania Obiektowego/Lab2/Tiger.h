#pragma once
#include "Animal.h"
#include <iostream>
#include <string>
using std::cout, std::string;

class Tiger final : public Animal
{
public:
	Tiger() : Animal() { cout << "\nDefault constructor of derived class 'Tiger'"; }
	~Tiger() { cout << "\nDestructor of derived class 'Tiger'"; }

	void roar(void);
	void set_type(string);
	void display_information(void);
};

void Tiger::roar(void) {
	cout << "\nrrrrr";
}

void Tiger::set_type(string type) {
	type_ = type;
}

void Tiger::display_information(void) {
	cout << "\nIt's a " << type_;
}