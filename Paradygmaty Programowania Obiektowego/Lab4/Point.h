#pragma once
#include <iostream>

template <class T, class U>
class Point
{
private:
	T x_;
	U y_;
public:
	Point<T, U>(T x, U y) : x_{ x }, y_{ y } {}

	T get_x(void) const {
		return x_;
	}

	U get_y(void) const {
		return y_;
	}

	void set_x(T x) {
		x_ = x;
	}

	void set_y(U y) {
		y_ = y;
	}

	void show(void);
};

template <typename T, typename U>
void Point<T, U>::show(void) {
	std::cout << "Coordinates:\nx = " << x_ << " \ny = " << y_ << "\n";
}