#include <iostream>
#include <conio.h>

using std::cout, std::cin, std::endl;

const int N = 15;
void menu(void); 
void input(char (&)[]);
void print(char []);
int length(char []);
void lowerToUpper(char (&)[]);
void upperToLower(char (&)[]);

int main(void){
    char tab[N], choice = '1';
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
                input(tab);
                print(tab);
                break;
            }
            case '2':{
                print(tab);
                break;
            }
            case '3':{
                cout << endl << length(tab) << endl;
                break;
            }
            case '4':{
                lowerToUpper(tab);
                print(tab);
                break;
            }
            case '5':{
                upperToLower(tab);
                print(tab);
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
}

void menu(void){
    cout << "Choose one of the following options" << endl
    << "0. Shut the program" << endl
    << "1. Input" << endl
    << "2. Print" << endl
    << "3. Length" << endl
    << "4. Lower to upper" << endl
    << "5. Upper to lower" << endl;
}

void input(char (&a)[]){
    cin.getline(a, N+1); 
}

void print(char a[]){
    cout << endl;
    for(int i = 0; i < N; i++){
        if(a[i] == 0)
            break;    
        cout << a[i];
    }
    cout << endl;
}

int length(char a[]){
    int result = 0;
    for(int i = 0; i < N; i++){
        if(a[i] == 0)
            break;
        result += 1;
    }
    return result;
}

void lowerToUpper(char (&a)[]){
    for(int i = 0; i < N; i++){
        if(a[i] == 0)
            break;
        else if(a[i] >= 97 && a[i] <= 122)
            a[i] -= 32;
    }
}

void upperToLower(char (&a)[]){
    for(int i = 0; i < N; i++){
        if(a[i] == 0)
            break;
        else if(a[i] >= 65 && a[i] <= 90)
            a[i] += 32;
    }
}