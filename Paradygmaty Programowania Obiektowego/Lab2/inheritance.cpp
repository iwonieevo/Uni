#include "inheritance.h"
#include "Animal.h"
#include "Tiger.h"
#include "Bear.h"
#include <iostream>
#include <string>
using std::cout, std::string;

void inheritance_main(void) {
	// ZADANIE NA 3.0
	cout << "ZADANIE NA 3.0\n\n";
	Tiger Timmy;
	Timmy.eat();
	cout << "\nWeight: " << Timmy.get_weight();
	cout << "\nColour: " << Timmy.get_colour();
	Timmy.roar();

	// ZADANIE NA 4.0
	cout << "\n\n\nZADANIE NA 4.0\n\n";
	Timmy.display_information();
	Timmy.set_type("mammal");
	Timmy.display_information();

	// ZADANIE NA 5.0
	cout << "\n\n\nZADANIE NA 5.0\n\n";
	Bear Teddy(300.0, "brown");
	cout << "\nWeight (Bear): " << Teddy.get_weight();
	cout << "\nColour (Bear): " << Teddy.get_colour();
	cout << "\nWeight (Animal): " << Teddy.Animal::get_weight();
	cout << "\nColour (Animal): " << Teddy.Animal::get_colour();

	// Destruktory wywoluja sie na zakonczenie programu wiec oddzielam te sekcje zeby byla bardziej widoczna
	cout << "\n\n\nDESTRUKTORY\n\n";
}


/*
*** PYTANIA - ZADANIE 1 ***

* A) Dzia�anie kt�rego konstruktora zaobserowa�e� i dlaczego?
Obu - i klasy bazowej i klasy pochodnej. Przy tworzeniu obiektu klasy pochodnej zawsze wywolywany jest tez konstruktor klasy bazowej. To troche tak jakby najpierw zostal utworozny obiekt klasy bazowej, a pozniej zostal nadpisany jako obiekt klasy pochodnej

* B) Czy uda�o si� wywo�a� metody klasy podstawowej dla obiektu klasy pochodnej? Dlaczego?
Tak. 'Tiger' dziedziczy od 'Animal' po specyfikatorze 'public' - wiec wszystkie metody public z 'Animal' sa tez automatycznie wszystkimi metodami public 'Tiger'

* C) Czy zauwa�y�e� dzia�anie destruktora? Je�eli tak, to jakiego i dlaczego?
Obu - i klasy bazowej i klasy pochodnej. Powod ten sam co w przypadku pytania A) - skoro utworzylismy obiekt pochodny, to znaczy ze utworzylismy tez obiekt bazowy - destruktory obu z nich sa wywolywane na koniec dzialania programu - mimo ze to teortycznie 1 obiekt



*** PYTANIA - ZADANIE 2 ***

* A) Wyja�nij dlaczego istnieje mo�liwo�� nadania warto�ci polu w klasie podstawowej poprzez metod� klasy pochodnej?
Poniewa� 'type_' jest w polu protected w 'Animal', to w 'Tiger' tez bedzie polem protected (bo dziedziczymy po public). Klasa ma dostep do sowich wlasnych elementow private i protected.



*** PYTANIA - ZADANIE 3 ***

* A) Wy�wietl warto�ci p�l prywatnych � wykorzystaj �gettery�. PYTANIE: Jakie warto�ci zosta�y wy�wietlone?
Te nadane przy stworzeniu obiektu 'Bear'

* B) Zakomentuj �gettery� w klasie Bear, ale pozostaw ich wywo�ania w g��wnej p�tli programu. PYTANIE: Jakie warto�ci teraz uzyska�e�?
Te nadane w konstruktorze domyslnym 'Animal'

* C) Co si� dzieje w momencie, gdy klasa pochodna i klasa podstawowa posiadaj� pola o tych samych nazwach?
Sa traktowane jako 2 rozne pola - nie sa overloadowane. Metody pochodne overloaduja metody z klasy bazowej i biora pola 'najglebiej' w hierarchii - te im najblizsze.

*/