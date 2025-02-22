#pragma once
#include "Enemy.h"

class Werewolf : public Enemy
{
private:
	float radius_;
public:
	Werewolf() : Enemy(), radius_(0.0) {}
	Werewolf(float x, float y, float strength, float radius)
		: Enemy(x, y, strength), radius_(radius) {}
	~Werewolf();

	float get_radius(void);
	void set_radius(float);
	virtual void show(void) override;
	virtual void attack(float) override;
	virtual void make_sound(void) override;
};