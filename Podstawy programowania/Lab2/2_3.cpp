#include <iostream>
#include <windows.h>

void draw(int);

int main()
{
    while(true)
    {   
        draw(2);
        draw(4);
        draw(6);
        draw(8); 
    }
}

void draw(int a)
{
    std::string x;
    for(int i = 0; i < a; i++)
        x += " *";
    x += "\n";
    for(int i = 0; i < a; i++)
        std::cout << x;
    Sleep(1000);
    system("cls");
}