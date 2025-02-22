#include <iostream>

int main()
{
    float a, b;
    char c;
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "Wprowadz znak operacji (+,-,*,/): "; \
    std::cin >> c;
    if (c == '/' && b == 0)
    {
        std::cout << "\nNie mozna dzielic przez 0";
    }
    else
    {
        switch (c)
        {
        case '+':
            std::cout << "\na + b = " << a + b;
            break;
        case '-':
            std::cout << "\na - b = " << a - b;
            break;
        case '*':
            std::cout << "\na * b = " << a * b;
            break;
        case '/':
            std::cout << "\na/b = " << a / b;
            break;
        default:
            std::cout << "\nNieznany znak operacji";
            break;
        }
        
    }
}


