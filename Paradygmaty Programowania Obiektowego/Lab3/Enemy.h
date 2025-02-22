#pragma once
#include <iostream>

class Enemy
{
protected:
	float x_;
	float y_;
	float strength_;

	Enemy()
		: x_(0.0), y_(0.0), strength_(0.0) {}

	Enemy(float x, float y, float strength)
		: x_(x), y_(y), strength_(strength) {}

public:
	virtual ~Enemy();

	float get_x(void);
	float get_y(void);
	float get_strength(void);
	void set_x(float);
	void set_y(float);
	void set_strength(float);
	void update_position(float, float);

	virtual void show(void) = 0;
	virtual void attack(float) = 0;
	virtual void make_sound(void) = 0;
};