#include <iostream>
#include <conio.h>
#include <algorithm> //std::count()

using std::cin, std::cout, std::endl, std::string;

int main(void){
    char letter;
    string input;
    int tab[26];
    for(int i = 0; i <= 25; i ++)
        tab[i] = 0;
    getline(cin, input);
    for(int i = 0; i <= 25; i++){
        letter = i + 65;
        tab[i] = std::count(input.begin(), input.end(), letter) + std::count(input.begin(), input.end(), letter + 32);
    }
    for(int i = 0; i <= 25; i++){
        if(tab[i] != 0){
            letter = i + 97;
            cout << letter << " ";
            for(int j = 0; j < tab[i]; j++)
                cout << "#";
            cout << endl;
        }
    }
    cout << endl << endl << "Press any key to continue...";
    getch();
}
