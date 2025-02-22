#include <iostream>
#include <random> //srand()
#include <ctime> //time()
#include <conio.h> //getch()
using std::cout, std::cin, std::endl;

const int N = 5; // >= 1
void menu(void);
void fill(int (&)[]);
int sum(int []);
int max(int []);
void print(int []);
void print_repetitives(int []);
void fill_rand(int (&)[], int, int);
void gen_bin(int, int (&)[]);
void bubblesort(int (&)[]);



int main(void){
    int tab[N];
    for(int i = 0; i < N; i++){
        tab[i] = 0;
    }
    char choice = '1';
    while(choice != '0'){
        system("cls");
        menu();
        cin >> choice;
        switch (choice){
            case '0':{
                system("cls");
                cout << "Shutting down the program.";
                break;
            }
            case '1':{
                fill(tab);
                print(tab);
                break;
            }
            case '2':{
                cout << "Sum: " << sum(tab);
                break;
            }
            case '3':{
                cout << "Max: " << max(tab);
                break;
            }
            case '4':{
                print(tab);
                break;
            }
            case '5':{
                cout << endl <<  "Elements with at least 3 occurences:" << endl;
                print_repetitives((tab));
                break;
            }
            case '6':{
                int a, b;
                cout << "Bottom limit: ";
                cin >> a;
                cout << "Top limit (including that number): ";
                cin >> b;
                fill_rand(tab, a, b);
                print(tab);
                break;
            }
            case '7':{
                int c, c_bin[5];
                cout << "Input number(DEC) to convert to BIN: ";
                cin >> c;
                if(c > 30 || c < 0){
                    cout << "Inputed number out of program range!";
                    break;
                }
                gen_bin(c, c_bin);
                for(int i = 0; i < 5; i++)
                    cout << c_bin[i];
                break;
            }
            case '8':{
                bubblesort(tab);
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
    << "1. Fill table manualy" << endl
    << "2. Sum all elements in the table" << endl
    << "3. Find max value in the table" << endl
    << "4. Print all elements of the table" << endl
    << "5. Print repetitive values in the table (at least 3 occurences)" << endl
    << "6. Fill the table with random integers in the given range" << endl
    << "7. Convert decimal number to binary (range 0-30)" << endl
    << "8. Bubble sort the table" << endl << endl;    
}

void fill(int (&t1)[]){
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        t1[i] = a;
    }
}

int sum(int t2[]){
    int result = 0;
    for(int i = 0; i < N; i++)
        result += t2[i];
    return result;
}

int max(int t3[]){
    int result = t3[0];
    for(int i = 0; i < N; i++){
        if(t3[i] > result)
            result = t3[i];
    }
    return result;
}

void print(int t4[]){
    cout << "Elements of the table:\n";
    for(int i = 0; i < N; i++)
        cout << "tab[" << i << "]=" << t4[i] << endl;
}

void print_repetitives(int t5[]){
    bool checked;
    int already_checked[N], counter = 0;

    for(int i = 0; i < N; i++){
        counter = 0, checked = false, counter = false;

        for(int j = 0; j < N; j++){
            if(t5[i] == already_checked[j])
                checked = true;
        }

        if(!checked){
            for(int j = 0; j < N; j++){
                if(t5[i] == t5[j])
                    counter++;
            }
        }
        
        if((counter >= 3) && !checked)
            cout << t5[i] << " x" << counter << "; ";

        if(!checked)
            already_checked[i] = t5[i];
        
    }
}

void fill_rand(int (&t6)[], int down, int up){
    srand(time(NULL));
    for(int i = 0; i < N; i++)
        t6[i] = down + rand()%(up - down + 1);
}

void gen_bin(int number, int (&number_bin)[]){
    for(int i = 0; i < 5; i++){
        number_bin[4 - i] = number % 2;
        number /= 2;
    }
}

void bubblesort(int (&to_sort)[]){
    int temp;
    for(int i = 0; i < N - 1; i++){
        for(int j = 0; j < N - i - 1; j++){
            if(to_sort[j] > to_sort[j + 1]){
                temp = to_sort[j];
                to_sort[j] = to_sort[j + 1];
                to_sort[j + 1] = temp;
            }
        }
    }
}
