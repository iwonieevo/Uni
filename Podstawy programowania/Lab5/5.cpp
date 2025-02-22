#include <iostream>
#include <fstream>
#include <conio.h> // getch()
#include <vector>
#include <bits/stdc++.h> // std::sort()
#include <random>
#include <string> // find() i string slice'ing

using std::cin, std::cout, std::string, std::endl, std::fstream, std::vector, std::getline;

struct student{
    string index, name, surname, dob; // assumptions: index - 6 digit number; name and surname - whatever; dob - dd.mm.yyyy
    char sex;                                      // sex - 'M' or 'F' - AMAB or AFAB (Assigned Male/Female At Birth) 
};
const string months = "01;02;03;04;05;06;07;08;09;10;11;12";
const string days = "01;02;03;04;05;06;07;08;09;10;11;12;13;14;15;16;17;18;19;20;21;22;23;24;25;26;27;28;29;30;31";

void menu(void);
void load(vector <student>&, string&);
void save(vector <student>&, string&);
void show(string&);
void show_base(vector <student>&);

bool compareIndex(student&, student&);
bool compareName(student&, student&);
bool compareSurname(student&, student&);
bool compareDoB(student&, student&);
bool compareSex(student&, student&);

int main(void){
    vector <student> base;
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
                string path;
                cout << endl << "Enter path to the file:\n";
                cin >> path;
                load(base, path);
                show_base(base);
                break;
            }
            case '2':{
                string path;
                cout << endl << "Enter path to the file:\n";
                cin >> path;
                save(base, path);
                show(path);
                break;
            }
            case '3':{
                string path;
                cout << endl << "Enter path to the file:\n";
                cin >> path;
                show(path);
                break;
            }
            case '4':{
                student S;
                bool valid = true;
                cout << endl << "Input info about student you want to add to the base:"
                << endl << "Index (6 digit number): ";
                cin >> S.index;
                if(S.index.size() != 6){
                    valid = false;
                    cout << endl << "Incorrect input!";
                }
                else{
                    for(auto c:S.index){
                        if(valid){
                            if(c < 48 or c > 57){
                                valid = false;
                                cout << endl << "Incorrect input!";
                            }
                        }
                    }
                }
                if(valid){
                    cout << endl << "Name: ";
                    cin >> S.name;
                    cout << endl << "Surname: ";
                    cin >> S.surname;
                    cout << endl << "Date of birth (dd.mm.yyyy): ";
                    cin >> S.dob;
                    if(S.dob.size() != 10){
                        valid = false;
                        cout << endl << "Incorrect input!";
                    }
                    else{
                        if(S.dob[2] != '.' or S.dob[5] != '.' or days.find(string(S.dob.begin(), S.dob.begin() + 2)) == string::npos or
                            months.find(string(S.dob.begin() + 3, S.dob.begin() + 5)) == string::npos){
                            valid = false;
                            cout << endl << "Incorrect input!";
                        }
                        else{
                            for(int i = 6; i < 10; i++){
                                if(valid){
                                    if(S.dob[i] < 48 or S.dob[i] > 57){
                                        valid = false;
                                        cout << endl << "Incorrect input!";
                                    }
                                }
                            }
                        }
                    }
                    if(valid){
                        cout << endl << "Sex (M/F): ";
                        cin >> S.sex;
                        if(S.sex != 'M' && S.sex != 'F'){
                            valid = false;
                            cout << endl << "Incorrect input!";
                        }
                    }
                }
                if(valid)
                    base.push_back(S);
                break;
            }
            case '5':{
                string key;
                cout << endl << "Input index of a student to remove from the base: ";
                cin >> key;
                int i = 0;
                for(auto X:base){
                    if(X.index == key){
                        base.erase(base.begin() + i);
                        break;
                    }
                    i++;
                }
                break;
            }
            case '6':{
                show_base(base);
                break;
            }
            case '7':{
                char k;
                cout << endl << "Choose by which parameter you want to sort the students:"
                << endl << "1. Index"
                << endl << "2. Name"
                << endl << "3. Surname"
                << endl << "4. Date of birth"
                << endl << "5. Sex\n";
                k = getch();
                cout << "\nChosen option: " << k << endl;
                switch (k){
                    case '1':{
                        sort(base.begin(), base.end(), compareIndex);
                        break;
                    }
                    case '2':{
                        sort(base.begin(), base.end(), compareName);
                        break;
                    }
                    case '3':{
                        sort(base.begin(), base.end(), compareSurname);
                        break;
                    }
                    case '4':{
                        sort(base.begin(), base.end(), compareDoB);
                        break;
                    }
                    case '5':{
                        sort(base.begin(), base.end(), compareSex);
                        break;
                    }
                    default:{
                        cout << endl << "Incorrect input. Sorting didn't start.";
                        break;
                    }
                }
                show_base(base);
                break;
            }
            case '8':{
                if(base.size() > 0){
                    srand(time(NULL));
                    int i = rand()%(base.size());
                    cout << endl << "Your randomly chosen student is:\n"
                    << base[i].index << " " << base[i].name << " " << base[i].surname << " " << base[i].dob << " " << base[i].sex;
                }
                break;
            }
            case '9':{
                char k;
                string key;
                cout << endl << "Choose by which parameter you want to filter the students:"
                << endl << "1. Index"
                << endl << "2. Name"
                << endl << "3. Surname"
                << endl << "4. Date of birth"
                << endl << "5. Sex\n";
                k = getch();
                cout << "\nChosen option: " << k << endl;
                cout << "Input key: ";
                cin >> key;
                cout << endl;
                switch (k){
                    case '1':{
                        for(auto X:base){
                            if(X.index.find(key) != string::npos)
                                cout << X.index << " " << X.name << " " << X.surname << " " << X.dob << " " << X.sex << endl;
                        }
                        break;
                    }
                    case '2':{
                        for(auto X:base){
                            if(X.name.find(key) != string::npos)
                                cout << X.index << " " << X.name << " " << X.surname << " " << X.dob << " " << X.sex << endl;
                        }
                        break;
                    }
                    case '3':{
                        for(auto X:base){
                            if(X.surname.find(key) != string::npos)
                                cout << X.index << " " << X.name << " " << X.surname << " " << X.dob << " " << X.sex << endl;
                        }
                        break;
                    }
                    case '4':{
                        for(auto X:base){
                            if(X.dob.find(key) != string::npos)
                                cout << X.index << " " << X.name << " " << X.surname << " " << X.dob << " " << X.sex << endl;
                        }
                        break;
                    }
                    case '5':{
                        char n_key = key[0];
                        for(auto X:base){
                            if(X.sex == n_key)
                                cout << X.index << " " << X.name << " " << X.surname << " " << X.dob << " " << X.sex << endl;
                        }
                        break;
                    }
                    default:{
                        cout << endl << "Incorrect input.";
                        break;
                    }
                }
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
    << "1. Load data from file" << endl
    << "2. Save data to the file" << endl
    << "3. Show content of the file" << endl
    << "4. Add element to the base (not to the file!)" << endl
    << "5. Remove specific element from the base (not from the file!)" << endl
    << "6. Show content of the base" << endl
    << "7. Sort students in the base" << endl
    << "8. Randomly show info of one student in the base" << endl
    << "9. Show all students which fulfil the criteria" << endl;
}

void load(vector <student>& saved_data, string& path){
    fstream file;
    file.open(path, fstream::in);
    if(file.is_open()){
        while(!file.eof()){
            student X;
            file >> X.index >> X.name >> X.surname >> X.dob >> X.sex;
            saved_data.push_back(X);
        }
        saved_data.pop_back();
    }
    else
        cout << "\nSomething went wrong, couldn't open the file.\n";
    file.close();
    
}

void save(vector <student>& data_to_save, string& path){
    fstream file;
    file.open(path, fstream::out);
    if(file.is_open()){
        for(auto X:data_to_save){
            file << X.index << " " << X.name << " " << X.surname << " " << X.dob << " " << X.sex << endl;
        }
    }
    else
        cout << "\nSomething went wrong, couldn't open the file.\n";
    file.close();
}

void show(string& path){
    fstream file;
    file.open(path, fstream::in);
    if(file.is_open()){
        while(!file.eof()){
            string word;
            getline(file, word);
            cout << word << endl;
        }
    }
    else
        cout << "\nSomething went wrong, couldn't open the file.\n";
    file.close();
}

void show_base(vector <student>& data_to_show){
    cout << endl;
    for(auto X:data_to_show)
        cout << X.index << " " << X.name << " " << X.surname << " " << X.dob << " " << X.sex << endl;
}

bool compareIndex(student& A, student& B){
    char a, b;
    for(int i = 0; i < 6; i++){
        a = A.index[i];
        b = B.index[i];
        if(a < b)
            return true;
        if(a > b)
            return false;
    }
    return false;
}

bool compareName(student& A, student& B){
    char a, b;
    for(int i = 0; i < std::min(A.name.size(), B.name.size()); i++){
        a = A.name[i];
        b = B.name[i];
        if(a < b)
            return true;
        if(a > b)
            return false;
    }
    return (A.name.size() < B.name.size());
}

bool compareSurname(student& A, student& B){
    char a, b;
    for(int i = 0; i < std::min(A.surname.size(), B.surname.size()); i++){
        a = A.surname[i];
        b = B.surname[i];
        if(a < b)
            return true;
        if(a > b)
            return false;
    }
    return (A.surname.size() < B.surname.size());
}

bool compareDoB(student& A, student& B){
    char a, b;
    for(int i = 6; i < 10; i++){
        a = A.dob[i];
        b = B.dob[i];
        if(a < b)
            return true;
        if(a > b)
            return false;
    }
    for(int i = 3; i < 5; i++){
        a = A.dob[i];
        b = B.dob[i];
        if(a < b)
            return true;
        if(a > b)
            return false;
    }
    for(int i = 0; i < 2; i++){
        a = A.dob[i];
        b = B.dob[i];
        if(a < b)
            return true;
        if(a > b)
            return false;
    }
    return false;
}

bool compareSex(student& A, student& B){
    char a, b;
    a = A.sex;
    b = B.sex;
    return(a < b); 
}
