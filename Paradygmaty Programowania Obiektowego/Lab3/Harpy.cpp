#include "Harpy.h"
#include <iostream>

Harpy::~Harpy() {
	std::cout << "\nHarpy destroyed!\n";
}

float Harpy::get_height(void) {
	return height_;
}

void Harpy::set_height(float height) {
	height_ = height;
}

void Harpy::show(void) {
	std::cout << "\nThe Harpy is at point (" << get_x() << ", "
		<< get_y() << ") and its height is " << get_height() << ".\n";
}

void Harpy::attack(float factor) {
	set_strength(get_strength() * (1 - factor));
	set_height(1.85);
	make_sound();
}

void Harpy::make_sound(void) {
	std::cout << "\nHarpy's screak!\n";
}