#include <iostream>
#include <ctime>
#include <random>
#include <conio.h>
using std::cout, std::cin, std::endl;

int main(void){
    srand(time(NULL));
    int n = 16 + rand()%17;
    unsigned int *tab = new unsigned int[n];
    for(int i = 0, j = 1; i < n; i++, j *= 2)
        tab[i] = j;
    for(int i = 0; i < n; i++)
        printf("[%d] 2^%d = %u\n", i, i, tab[i]);
    delete[] tab;
    cout << endl << endl << "Press any key to continue...";
    getch();
}