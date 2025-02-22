#include "operator_OL.h"
#include "Weapon.h"
#include "Container.h"
#include "LegendaryWeapon.h"
#include <iostream>
#include <vector>
using std::cin, std::cout, std::vector;

void operator_OL_main(void) {
	Weapon Sword(0.0, 100.0, 5.0), Shield(50.0, 5.0, 1.0), Custom;
	cout << "*** Sword stats ***" << Sword;
	cout << "\n*** Shield stats ***" << Shield;
	cout << "\n*** Combined Sword&Shield stats ***" << Sword + Shield;
	
	cout << "\n*** Input Custom Weapon stats ***";
	cin >> Custom;
	cout << "*** Custom weapon stats ***" << Custom;

	cout << "\n*** Lootbag contents ***";
	Container Lootbag;
	Lootbag += Weapon(-10.0, 10.0, 10.0);
	Lootbag += Weapon(10.0, -10.0, 10.0);
	Lootbag += Weapon(10.0, 10.0, -10.0) + Weapon(10.0, 10.0, 10.0);
	cout << Lootbag;

	cout << "\n*** Converting Legendary Weapon to Casual Weapon";
	LegendaryWeapon EpicMace(20.0, 1000.0, 20.0, 5.0);
	cout << "\n\n* Legendary Weapon stats before convertion *" << EpicMace;
	Custom = static_cast<Weapon>(EpicMace);
	cout << "\n* Legendary Weapon stats after convertion *" << Custom;
}