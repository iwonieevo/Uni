#pragma once
#include "Weapon.h"
#include <iostream>
using std::cout, std::cin;

class LegendaryWeapon : public Weapon
{
private:
	double runic_power_;

public:
	LegendaryWeapon(double defense = 0.0, double damage = 0.0, double crit_chance = 0.0, double runic_power = 0.0)
		: Weapon(defense, damage, crit_chance), runic_power_{ runic_power }
	{}

	void set_runic_power(double runic_power) { runic_power_ = runic_power; }
	double get_runic_power(void) const { return runic_power_; }

	friend ostream& operator<<(ostream&, LegendaryWeapon const&);
};


ostream& operator<<(ostream& out, LegendaryWeapon const& W) {
	return out << "\nLegendary weapon stats:"
		<< "\nDefense: " << W.defense_
		<< "\nDamage: " << W.damage_
		<< "\nCritical hit chance: " << W.crit_chance_
		<< "\nRunic power: " << W.runic_power_
		<< "\n";
}