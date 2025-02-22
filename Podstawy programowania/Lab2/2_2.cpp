#include <iostream>

void menu();
int weirdSum();
int largestCommonDivisor(int, int);
void stairs(int);

int main()
{
    bool stop = false;
    char choice;
    while(!stop)
    {
        system("cls");
        menu();
        std::cout << "\n\nDo you wish to continue? (Y/N)\n";
        std::cin >> choice;
        if(choice == 'N' || choice == 'n')
            stop = true;
    }
}

void menu()
{
    char z;
    std::cout << "Choose one of the following options:\n"
    << "1. Weird sum\n"
    << "2. Largest common divisor\n"
    << "3. Draw stairs\n";
    std::cin >> z;
    switch (z) {
        case '1':
        {
            int result = weirdSum();
            std::cout << "Weird sum: " << result;
            break;
        }
        case '2':
        {
            int x, y;
            std::cout << "Please enter two positive integers which LCD you want to calculate:\n";
            std::cin >> x >> y;
            if(x <= 0 || y <= 0)
            {
                std::cout << "\nWrong input! Numbers must be two positive integers. Please, try again.";
                break;
            }
            std::cout << "LCD of " << x << " and " << y << ": " << largestCommonDivisor(x, y);
            break;
        }
        case '3':
        {
            int size;
            std::cout << "Enter the size of the stairs:\n";
            std::cin >> size;
            stairs(size);
            break;
        }
        default:
        {
            std::cout << "Incorrect option. Please try again.";
            break;
        }
    }
}

int weirdSum()
{
    int a = 0, sum = 0;
    while(a != 99)
    {
        std::cin >> a;
        if(-15 <= a && a <= 15)
            sum += a;
    }
    return sum;
}

int largestCommonDivisor(int a, int b)
{
    while( a != b)
    {
        if(a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}

void stairs(int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            std::cout <<  n - j << " ";
        }
        std::cout << std::endl;
    }
}
