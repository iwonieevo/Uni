#include <iostream>
#include <conio.h>
#include <algorithm> // std::copy()

using std::cout, std::cin, std::endl, std::string;

void menu(void);
void print(string [], int);
void add(string *&, int &, int &, string);
void remove(string *&, int &, int);

int main(void){
    int capacity = 4, size = 4;
    string value;
    string* tab = new string[capacity];
    tab[0] = "What's", tab[1] = "Up", tab[2] = "Dog", tab[3] = "?";
    char choice = '1';
    while(choice != '0'){
        system("cls");
        menu();
        choice = getch();
        cout << "Chosen option: " << choice << endl;

        switch (choice){
            case '0':{
                system("cls");
                cout << "Shutting down the program.";
                break;
            }
            case '1':{
                string value;
                cout << endl << "Input an element to be added at the end of the table: ";
                cin >> value;
                add(tab, size, capacity, value);
                break;
            }
            case '2':{
                int index;
                cout << endl << "Input index of an element to be removed from the table: ";
                cin >> index;
                remove(tab, size, index);
                break;
            }
            case '3':{
                print(tab, size);
                break;
            }
            case '4':{
                cout << endl << "Size: " << size << endl << "Capacity: " << capacity;
                break;
            }
            
            default:{
                cout << "Incorrect input! Please try again.";
                break;
            }
        }
        cout << endl << endl << "Press any key to continue...";
        getch();
    }
    delete[] tab;
}

void menu(void){
    cout << "Choose one of the following options" << endl
    << "0. Shut the program" << endl
    << "1. Add element" << endl
    << "2. Remove element" << endl
    << "3. Print available elements" << endl
    << "4. Print current size and capacity" << endl;
}

void print(string func_tab[], int tab_size){
    for(int i = 0; i < tab_size; i++)
        cout << "[" << i << "] " << func_tab[i] << endl;
}

void add(string *&tab_pointer, int &tab_size, int &tab_cap, string elem){
    if(tab_size >= tab_cap){
        tab_cap *= 2;
        string *newTab = new string[tab_cap];
        std::copy(tab_pointer, tab_pointer + tab_size, newTab); //pointer to the beginning of the source container, pointer to the end of the source container, pointer to the beginning of the destinated container
        delete[] tab_pointer;
        tab_pointer = newTab; //pointer set to point to the new tab
    }
    tab_pointer[tab_size++] = elem; 
}

void remove(string *&tab_pointer, int &tab_size, int ind){
    if(ind >= 0 && ind < tab_size){
        for(int i = ind; i < tab_size - 1; i++)
            tab_pointer[i] = tab_pointer[i + 1];
        tab_size--;
    }
    else
        cout << "There is no such index in this table.";
}