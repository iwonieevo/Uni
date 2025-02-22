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

* A) Dzia³anie którego konstruktora zaobserowa³eœ i dlaczego?
Obu - i klasy bazowej i klasy pochodnej. Przy tworzeniu obiektu klasy pochodnej zawsze wywolywany jest tez konstruktor klasy bazowej. To troche tak jakby najpierw zostal utworozny obiekt klasy bazowej, a pozniej zostal nadpisany jako obiekt klasy pochodnej

* B) Czy uda³o siê wywo³aæ metody klasy podstawowej dla obiektu klasy pochodnej? Dlaczego?
Tak. 'Tiger' dziedziczy od 'Animal' po specyfikatorze 'public' - wiec wszystkie metody public z 'Animal' sa tez automatycznie wszystkimi metodami public 'Tiger'

* C) Czy zauwa¿y³eœ dzia³anie destruktora? Je¿eli tak, to jakiego i dlaczego?
Obu - i klasy bazowej i klasy pochodnej. Powod ten sam co w przypadku pytania A) - skoro utworzylismy obiekt pochodny, to znaczy ze utworzylismy tez obiekt bazowy - destruktory obu z nich sa wywolywane na koniec dzialania programu - mimo ze to teortycznie 1 obiekt



*** PYTANIA - ZADANIE 2 ***

* A) Wyjaœnij dlaczego istnieje mo¿liwoœæ nadania wartoœci polu w klasie podstawowej poprzez metodê klasy pochodnej?
Poniewa¿ 'type_' jest w polu protected w 'Animal', to w 'Tiger' tez bedzie polem protected (bo dziedziczymy po public). Klasa ma dostep do sowich wlasnych elementow private i protected.



*** PYTANIA - ZADANIE 3 ***

* A) Wyœwietl wartoœci pól prywatnych – wykorzystaj „gettery”. PYTANIE: Jakie wartoœci zosta³y wyœwietlone?
Te nadane przy stworzeniu obiektu 'Bear'

* B) Zakomentuj „gettery” w klasie Bear, ale pozostaw ich wywo³ania w g³ównej pêtli programu. PYTANIE: Jakie wartoœci teraz uzyska³eœ?
Te nadane w konstruktorze domyslnym 'Animal'

* C) Co siê dzieje w momencie, gdy klasa pochodna i klasa podstawowa posiadaj¹ pola o tych samych nazwach?
Sa traktowane jako 2 rozne pola - nie sa overloadowane. Metody pochodne overloaduja metody z klasy bazowej i biora pola 'najglebiej' w hierarchii - te im najblizsze.

*/