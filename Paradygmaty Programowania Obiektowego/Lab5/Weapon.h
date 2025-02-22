#pragma once
#include <iostream>
using std::cout, std::cin, std::ostream, std::istream;

class Weapon
{
protected:
	double defense_;
	double damage_;
	double crit_chance_;

public:
	Weapon(double defense = 0.0, double damage = 0.0, double crit_chance = 0.0)
		: defense_{ defense }, damage_{ damage }, crit_chance_{ crit_chance }
	{}
	void set_defense(double defense) { defense_ = defense; }
	void set_damage(double damage) { damage_ = damage; }
	void set_crit_chance(double crit_chance) { crit_chance_ = crit_chance; }
	double get_defense(void) const { return defense_; }
	double get_damage(void) const { return damage_; }
	double get_crit_chance(void) const { return crit_chance_; }

	friend Weapon operator+(Weapon const&, Weapon const&);
	friend ostream& operator<<(ostream&, Weapon const&);
	friend istream& operator>>(istream&, Weapon&);
};

Weapon operator+(Weapon const& W1, Weapon const& W2) {
	return Weapon(W1.defense_ + W2.defense_,
		W1.damage_ + W2.damage_,
		W1.crit_chance_ + W2.crit_chance_);
}

ostream& operator<<(ostream& out, Weapon const& W) {
	return out << "\nCommon weapon stats:"
		<< "\nDefense: " << W.defense_
		<< "\nDamage: " << W.damage_
		<< "\nCritical hit chance: " << W.crit_chance_
		<< "\n";
}

istream& operator>>(istream& in, Weapon& W) {
	cout << "\nINPUT VALUES: ";
	cout << "\nDefense: ";
	in >> W.defense_;
	cout << "Damage: ";
	in >> W.damage_;
	cout << "Critical hit chance: ";
	in >> W.crit_chance_;
	cout << "\n";
	return in;
}