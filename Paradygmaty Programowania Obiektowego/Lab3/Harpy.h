#pragma once

#include "Enemy.h"
#include <iostream>

class Harpy : public Enemy
{
private:
	float height_;

public:
	Harpy() : Enemy(), height_(0.0) {}
	Harpy(float x, float y, float strength, float height)
		: Enemy(x, y, strength), height_(height) {}
	~Harpy();

	float get_height(void);
	void set_height(float);
	virtual void show(void) override;
	virtual void attack(float) override;
	virtual void make_sound(void) override;
};