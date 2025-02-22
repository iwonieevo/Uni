#include "polymorphism.h"
#include "Enemy.h"
#include "Harpy.h"
#include "Werewolf.h"
#include <iostream>
using std::cout;

void polymorphism_main(void) {
	//ZADANIE NA 3.0
	cout << "|------------ZADANIE 3.0------------|\n\n";

	Enemy* Doppler = nullptr;
	Harpy* Helena = new Harpy(5.0, 5.0, 100.0, 10.0);
	Werewolf* Waldemar = new Werewolf(-5.0, -5.0, 200.0, 3.0);

	cout << "\nDoppler is impersonating Harpy!\n";
	Doppler = Helena;
	Doppler->show();
	Doppler->update_position(5.0, -5.0);
	Doppler->attack(0.01);
	Doppler->show();

	cout << "\n\nDoppler is impersonating Werewolf!\n";
	Doppler = Waldemar;
	Doppler->show();
	Doppler->update_position(1.0, 20.0);
	Doppler->attack(0.5);
	Doppler->show();

	cout << "\n\nSpace for destructors:\n";
	delete Helena;
	delete Waldemar;

	//ZADANIE NA 4.0
	cout << "\n\n|------------ZADANIE 4.0------------|\n\n";
	Enemy** MonsterNest = new Enemy*[4];
	Harpy* Hania = new Harpy(-20.0, 30.0, 50.0, 50.0);
	Harpy* Henrietta = new Harpy(3.0, 4.0, 200.0, 30.0);
	Werewolf* Wojtek = new Werewolf(50.0, -5.0, 1000.0, 2.0);
	Werewolf* Wiesiek = new Werewolf(6.0, 200.0, 2000.0, 1.0);

	MonsterNest[0] = Hania;
	MonsterNest[1] = Henrietta;
	MonsterNest[2] = Wojtek;
	MonsterNest[3] = Wiesiek;

	for (int i = 0; i < 4; i++) {
		cout << "\n\n* Enemy #" << i + 1 << " *\n";
		MonsterNest[i]->show();
		cout << "Strength: " << MonsterNest[i]->get_strength() << "\n";
		MonsterNest[i]->update_position(10.0, 10.0);
		MonsterNest[i]->attack(0.2);
		cout << "\nStrength: " << MonsterNest[i]->get_strength();
		MonsterNest[i]->show();
	}

	cout << "\n\n\nSpace for destructors:\n";
	delete Hania;
	delete Henrietta;
	delete Wojtek;
	delete Wiesiek;
}

/*
***PYTANIE 1***
Jak myœlisz, dlaczego pola klasy Enemy s¹ protected, a nie private?
* - ¿ebym siê zastanwia³ ;). A tak na serio to ¿eby klasy pochodne mia³y dostêp
* do prywatnych (no w tym wypadku chronionych) pól klasy bazowej

***PYTANIE 2***
Czy mo¿na wskaŸnikowi klasy pochodnej przypisaæ wskaŸnik klasy bazowej?
* - Nie O.o

***PYTANIE 3***
Czym siê ró¿ni¹ metody czysto wirtualne od wirtualnych?
* - metody wirtualne umo¿liwiaj¹ stworzenie obeiktu klasy bazowej, podczas gdy
* metoda czysto wirtualna to jedynie czesc interfejsu jakim
* jest klasa abstrtakcyjna.
* Klasy czysto wirtualne nie maja tez definicji.

***PYTANIE 4***
Które ze stworzonych klas s¹ klasami abstrakcyjnymi? Uzasadnij odpowiedŸ.
* - jedynie klasa bazowa 'Enemy', poniewaz zawiera min. 1 (dokladnie to 3)
* metody czysto wirtualne, podczas gdy ani 'Werewolf' ani 'Harpy' nie ma ani
* jednej takiej metody (nadpisuja tylko metody czysto wirtualne klasy 'Enemy')
*/