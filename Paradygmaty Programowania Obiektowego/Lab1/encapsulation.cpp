#include "Player.h"
#include "encapsulation.h"
#include <iostream>
#include <string>

void encapsulation_main(void) {
	Player Iwo;
	Player Julka;
	Player Kazik("Bot Patryk", 20, 0.5, -1.5);
	
	Iwo.print_method();
	Julka.print_method();
	Kazik.print_method();
	Iwo.save_method();
	Julka.set_nick("Kulka");
	Kazik.set_level(200);
	cout << "\nNICK OBIEKTU IWO: " << Iwo.get_nick();
	cout << "\nNICK OBIEKTU JULKA: " << Julka.get_nick();
	Kazik.print_method();
	
}
/*
void save_func(Player &Iksinski) {
	cout << "\nInput nick: ";
	getline(cin, Iksinski._nick);
	cout << "\nInput level: ";
	cin >> Iksinski._level;
	cout << "\nInput position x: ";
	cin >> Iksinski._x;
	cout << "\nInput position y: ";
	cin >> Iksinski._y;
}

void print_func(Player &Iksinski) {
	cout << "\nNick: " << Iksinski._nick << "\nLevel: " << Iksinski._level << "\nPosition x: " << Iksinski._x << "\nPosition y: " << Iksinski._y;
}
*/

/*PYTANIE: Czy stworzone przez Ciebie funkcje sk�adowe i funkcje nie b�d�ce sk�adowymi klasy b�d� nadal dzia�a�? Je�li tak, to kt�re i dlaczego? (Niedzia�aj�ce elementy
zakomentuj)

-powyzsze funkcje nie beda dzialac, o ile pola klasy nie beda w dostepie publicznym

-metody klasy beda dzialac niezaleznie od dostepnosci pol klasy

-jest tak poniewaz metody sa czescia klasy, a wiec maja dostep do jej calosci, a funkcje sa poza klasa, wiec maja dostep tylko do tych pol klasy ktore sa publiczne*/

/*PYTANIE: Czy dla stworzonego obiektu zosta�y wy�wietlone warto�ci, kt�re nada�e�
 poprzez konstruktor?

-tak*/

/*PYTANIE: Czy zauwa�y�e� dzia�anie destruktora? Czy musia�e� go wywo�a� jawnie?

-Tak, zauwazylem

-Nie, wywolal sie automatycznie na zakonczenie dzialania programu*/

/*PYTANIE: Przetestuj i odpowiedz, w jakiej kolejno�ci wywo�aj� si� destruktory w przypadku utworzenia obiektu za pomoc� konstruktora domy�lnego, a potem kolejnego za
pomoc� konstruktora wieloargumentowego?

-Po dodaniu wiekszej ilosci obiektow, mozna zauwazyc ze destruktory wywoluja sie w odwrotnej kolejnosci niz zostaly utworzone obiekty*/

/*PYTANIE: Wyja�nij, dlaczego akurat przy tych funkcjach u�y�e� s�owa kluczowego
(dodatkowo podaj jakie to s�owo)?

-chodzi o slowo kluczowe const

-uzylem go przy funckjach dostepowych, poniewaz w zalozeniu maja one zwrocic wartosci, a nie je zmieniac, uzycie const zapobiega temu i dodatkowo sluzy jako alias informujacy*/

/*PYTANIE: Je�eli klasa posiada konstruktor wieloargumentowy, to konieczne by�o
zdefiniowanie konstruktora domy�lnego jawnie, aby m�g� on zosta� wywo�any? Czy
gdyby� tego nie zrobi�, zosta�by wywo�any niejawnie? (Przetestuj i zastan�w si�, dlaczego)

-obiekty stworzone z uzyciem konstruktora wieloargumentowego normalnie tworzyly sie nawet przy prywatnym (lub po prostu braku) konstruktorze domyslnym

-by obiekty mogly byc tworzone z uzyciem konstruktora domyslnego, przy jednoczesnym istnieniu zdefiniowanego konstruktora wieloargumentowego, konstruktor domyslny musi byc 
 zdefiniowany i dostepny publicznie - jest tak, poniewaz obiekty tworzone sa poza klasa, wiec zeby zostac stworzone musza miec najpierw dostep do kontruktora*/