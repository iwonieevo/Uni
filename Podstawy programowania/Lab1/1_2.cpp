#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
	double a, b, c;
	int d;
	std::cout << "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;
	std::cout << "c = ";
	std::cin >> c;
	std::cout << "Precyzja = ";
	std::cin >> d;
	std::cout << "\nf(x) = ";
	if (a != 0 && a != 1)
		std::cout << a << "x\xFD ";
	else if (a == 1)
		std::cout << "x\xFD ";
	if (b > 0 && b != 1 && b != -1)
		std::cout << "+" << b << "x ";
	else if (b < 0 && b != 1 && b != -1)
		std::cout << b << "x ";
	else if (b == 1)
		std::cout << "+x ";
	else if (b == -1)
		std::cout << "-x ";
	if (c > 0)
		std::cout << "+" << c;
	else if (c < 0)
		std::cout << c;
	else
		std::cout << "0";
	std::cout << std::endl;

	if (a == 0)
	{
		if (b == 0)
		{
			if (c == 0)
				std::cout << "\nPodana funkcja jest stala i ma nieskonczenie wiele miejsc zerowych";
			else
				std::cout << "\nPodana funkcja jest stala i nie ma miejsc zerowych";
		}
		else
		{
			std::cout << "\nPodana funkcja jest liniowa i ma miejsce zerowe w x0 = "
				<< std::setprecision(d) << -c / b;
		}
	}
	else
	{
		const double delta = (pow(b, 2) - 4 * a * c);
		std::cout << "\nPodana funkcja jest kwadratowa i ";

		if (delta > 0)
		{
			std::cout << "ma 2 miejsca zerowe\nx1 = " << std::setprecision(d) << (-b - sqrt(delta)) / (2 * a)
				<< "\nx2 = " << std::setprecision(d) << (-b + sqrt(delta)) / (2 * a);
		}
		else if (delta == 0)
		{
			std::cout << "ma 1 miejsce zerowe\nx0 = " << std::setprecision(d) << -b / (2 * a);
		}
		else
			std::cout << "nie ma miejsc zerowych";
	}
}