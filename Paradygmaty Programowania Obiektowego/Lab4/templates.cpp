#include "templates.h"
#include "Point.h"
#include "Comparison.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T, typename U>
void randomize_Point(Point<T, U>&);

template <typename T, typename U>
void randomize_Point(Point<T, U>&, float, float);



void templates_main(void) {
	srand(time(NULL));
	std::cout << "**** SPECIFIC VALUES ****\n\n\n";
	Point<int, int> Harpy1(4, 2);
	Point<int, int> Harpy2(8, 1);
	Point<double, double> Werewolf1(0.2, 0.3);
	Point<double, double> Werewolf2(3.7, 4.2);
	Point<double, int> Human1(4.5, 2);
	Point<double, int> Human2(-8.3, 3);
	Comparison<int, int> Harpies(Harpy1, Harpy2);
	Comparison<double, double> Werewolves(Werewolf1, Werewolf2);
	Comparison<double, int> Humans(Human1, Human2);
	std::cout << "\n*** Harpies ***\n";
	Harpies.show_all();
	std::cout << "\n*** Werewolves ***\n";
	Werewolves.show_all();
	std::cout << "\n*** Humans ***\n";
	Humans.show_all();

	std::cout << "\n\n\n**** RANDOM VALUES ****\n\n\n";
	randomize_Point(Harpy1, -500.0, 500.0);
	randomize_Point(Harpy2);
	randomize_Point(Werewolf1, -100.0, 100.0);
	randomize_Point(Werewolf2);
	randomize_Point(Human1, -10.0, 10.0);
	randomize_Point(Human2);
	Harpies.set_First(Harpy1);
	Harpies.set_Second(Harpy2);
	Werewolves.set_First(Werewolf1);
	Werewolves.set_Second(Werewolf2);
	Humans.set_First(Human1);
	Humans.set_Second(Human2);
	std::cout << "\n*** Harpies ***\n";
	Harpies.show_all();
	std::cout << "\n*** Werewolves ***\n";
	Werewolves.show_all();
	std::cout << "\n*** Humans ***\n";
	Humans.show_all();
}


template <typename T, typename U>
void randomize_Point(Point<T, U>& CurrentPoint) {
	CurrentPoint.set_x(((float)std::rand() / RAND_MAX) * 100 - 50);
	CurrentPoint.set_y(((float)std::rand() / RAND_MAX) * 100 - 50);
}
//defaultowy zakres randomizera [-50; 50]

template <typename T, typename U>
void randomize_Point(Point<T, U>& CurrentPoint, float start, float end) {
	CurrentPoint.set_x(((float)std::rand() / RAND_MAX) * (end - start) + start);
	CurrentPoint.set_y(((float)std::rand() / RAND_MAX) * (end - start) + start);
}
//to troche integralnie nie ma sensu przy szablonach z wieloma typami (a nie 1 jak w instrukcji) 
// zeby start i end byly typami T i U, wiec zmieniam na float