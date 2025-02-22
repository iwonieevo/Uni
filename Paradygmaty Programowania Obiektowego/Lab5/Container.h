#pragma once
#include "Weapon.h"
#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector, std::ostream;

class Container
{
private:
	vector<Weapon> Contents_;

public:
	vector <Weapon> get_container(void) { return Contents_; }
	void set_container(vector <Weapon> Container) { Contents_ = Container; }

	friend Container operator+=(Container&, Weapon const&);
	friend ostream& operator<<(ostream&, Container const&);
};

Container operator+=(Container& C, Weapon const& W) {
	C.Contents_.push_back(W);
	return C;
}

ostream& operator<<(ostream& out, Container const& C) {
	out << "\n\n* Container contents *\n";
	for (auto& it : C.Contents_) {
		out << it;
	}
	return out << "\n";
}

/* 
*** ALTERNATYWNE ITEROWANIE PO WEKTORZE ***

for (vector<Weapon>::const_iterator iter = C.Contents_.begin(); iter != C.Contents_.end(); iter++) {
		out << *iter;
	}
*/
