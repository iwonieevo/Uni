#pragma once
#include <iostream>
#include <string>
using std::cout, std::string;

class Animal
{
private:
	float weight_;
	string colour_;
protected:
	string type_;
public:
	Animal() : weight_{ 0.0 }, colour_{ "none" } { cout << "\nDefault constructor of base class 'Animal'"; }
	~Animal() { cout << "\nDestructor of base class 'Animal'"; }

	void eat(void);
	float get_weight(void) const;
	string get_colour(void) const;
};

void Animal::eat(void) {
	cout << "\nI can eat!";
}

float Animal::get_weight(void) const{
	return weight_;
}

string Animal::get_colour(void) const{
	return colour_;
}
