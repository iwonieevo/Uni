#pragma once
#include "Animal.h"
#include <iostream>
#include <string>
using std::cout, std::string;

class Bear final : public Animal
{
private:
	float weight_;
	string colour_;
public:
	Bear(float weight, string colour) 
		: weight_{weight}
		, colour_{colour} 
	{
		cout << "\nMulti-arg constructor of derived class 'Bear";
	}
	~Bear() { cout << "\nDestructor of derived class 'Bear"; }

	float get_weight(void) const;
	string get_colour(void) const;
};

float Bear::get_weight(void) const {
	return weight_;
}

string Bear::get_colour(void) const {
	return colour_;
}