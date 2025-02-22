#pragma once
#include "Point.h"
#include <iostream>
#include <math.h>
#include <cmath>
constexpr float M_PI = 3.14159265358979323846;

template <class T, class U>
class Comparison
{
private:
	Point<T, U> First_;
	Point<T, U> Second_;
	float solution_;
public:
	Comparison<T, U>(Point<T, U> First, Point<T, U> Second) : First_{ First }, Second_{ Second } {}

	Point<T, U> get_First(void) const {
		return First_;
	}

	Point<T, U> get_Second(void) const {
		return Second_;
	}

	float get_solution(void) const {
		return solution_;
	}

	void set_First(Point<T, U> First) {
		First_ = First;
	}

	void set_Second(Point<T, U> Second) {
		Second_ = Second;
	}

	void show_cords(void);
	void distance(void);
	Point<T, U> center(void);
	float circumference(void);
	void show_all(void);
};

template <typename T, typename U>
void Comparison<T, U>::show_cords(void) {
	std::cout << "First Point: ";
	First_.show();
	std::cout << "\nSecond Point: ";
	Second_.show();
	std::cout << "\n";
}

template <typename T, typename U>
void Comparison<T, U>::distance(void) {
	solution_ = sqrt(pow(First_.get_x() - Second_.get_x(), 2) + pow(First_.get_y() - Second_.get_y(), 2));
}

template <typename T, typename U>
Point<T, U> Comparison<T, U>::center() {
	T x_val = (First_.get_x() + Second_.get_x()) * 0.5;
	U y_val = (First_.get_y() + Second_.get_y()) * 0.5;
	Point<T, U> Center(x_val, y_val);
	return Center;
}
//NOTE: to nie bedzie zawsze prawdziwa wartosc srodka, bo Center to obiekt Point<T, U>, wiec jezeli T bedzie
//np. typu int, a prawdziwa wartosc x srodka nie bedzie liczba calkowita, to zostanie ona zaokraglona

template <typename T, typename U>
float Comparison<T, U>::circumference(void) {
	distance();
	return M_PI * solution_;
}

template <typename T, typename U>
void Comparison<T, U>::show_all(void) {
	distance();
	show_cords();
	std::cout << "Distance: " << get_solution() << "\n";
	std::cout << "Center ";
	center().show();
	std::cout << "Circumference: " << circumference() << "\n";
}