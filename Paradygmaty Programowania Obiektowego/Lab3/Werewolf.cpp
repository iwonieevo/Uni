#include "Werewolf.h"
#include <iostream>

Werewolf::~Werewolf() {
	std::cout << "\nWerewolf destroyed!\n";
}

float Werewolf::get_radius(void) {
	return radius_;
}

void Werewolf::set_radius(float radius) {
	radius_ = radius;
}

void Werewolf::show(void) {
	std::cout << "\nThe Werewolf is at point (" << get_x() << ", "
		<< get_y() << ") and its radius is " << get_radius() << ".\n";
}

void Werewolf::attack(float factor) {
	set_strength(get_strength()*(1 - factor));
	set_radius(get_radius() * 1.5);
	make_sound();
}

void Werewolf::make_sound(void) {
	std::cout << "\nWerewolf's growl!\n";
}