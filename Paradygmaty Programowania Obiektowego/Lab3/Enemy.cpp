#include "Enemy.h"

Enemy::~Enemy() {
	std::cout << "\nEnemy destroyed!\n";
}

float Enemy::get_x(void) {
	return x_;
}

float Enemy::get_y(void) {
	return y_;
}

float Enemy::get_strength(void) {
	return strength_;
}

void Enemy::set_x(float x) {
	x_ = x;
}

void Enemy::set_y(float y) {
	y_ = y;
}

void Enemy::set_strength(float strength) {
	strength_ = strength;
}

void Enemy::update_position(float x, float y) {
	set_x(get_x() + x);
	set_y(get_y() + y);
}
