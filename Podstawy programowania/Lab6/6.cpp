#include <iostream>
#include <conio.h>

using std::cout, std::cin, std::string, std::endl;

struct student {
	string name, surname, index;
	int age;
	char sex;
	student *next = 0; 
};

struct queue {
	student *first = 0;
	size_t size = 0;
	void push_back (string name_ta, string surname_ta, string index_ta, int age_ta, char sex_ta);
	void pop_first (void);
	void print_queue (void);
	void print_elem (int n);
};

void queue::print_elem (int n) {
	if(size <= n || n < 0) {
		cout << "Nie ma elementu o takiej lp w bazie. Dostepne numery 0-" << size-1;
		return;
	}

	student *temp = first;
	while (n > 0) {
		temp=temp->next;
		n--;
	}

	cout << "imie: " << temp->name << "; nazwisko: " << temp->surname << "; indeks: " << temp->index << "; wiek: " << temp->age << "; plec: " << temp->sex << endl;
}

void queue::print_queue (void) {
	student *temp = first;
	while (temp) {
		cout << "imie: " << temp->name << "; nazwisko: " << temp->surname << "; indeks: " << temp->index << "; wiek: " << temp->age << "; plec: " << temp->sex << endl;
		temp=temp->next;
	}
}

void queue::pop_first (void) {
	student *temp = first;
	first = temp->next;
	delete temp;
	size -= 1;
}

void queue::push_back(string name_ta, string surname_ta, string index_ta, int age_ta, char sex_ta) {
	student *to_add = new student;

	to_add->name = name_ta;
	to_add->surname = surname_ta;
	to_add->index = index_ta;
	to_add->age = age_ta;
	to_add->sex = sex_ta;

	if (first==0) first = to_add;
	
	else {
		student *temp = first;

		while (temp->next) temp = temp->next;

		temp->next = to_add; 
	}

	delete to_add;

	size += 1;
}

void menu (void) {
	cout << "Wybierz jedna z ponizszych opcji:" << endl
	<< "0. Zamknij baze" << endl
	<< "1. Wyswietl baze" << endl
	<< "2. Wyswietl element o konkretnej lp w bazie (numerowanie od 0)" << endl
	<< "3. Dodaj element na koniec bazy" << endl
	<< "4. Usun pierwszy element z bazy" << endl;
}


int main() {
	queue *database = new queue;
	char choice = '1';
	while (choice != '0') {
		system("cls");
        menu();
        choice = getch();
        cout << "Chosen option: " << choice << endl;

		switch (choice) {
			case '0': {
				system("cls");
                cout << "Zamykanie bazy...";
				break;
			}
			case '1': {
				database->print_queue();
				break;
			}
			case '2': {
				int i;
				cout << "Podaj lp elementu, ktory chcesz wyswietlic: ";
				cin >> i;
				database->print_elem(i);
				break;
			}
			case '3': {
				string a, b, c;
				int d;
				char e;
				cout << "Wprowadz dane do dodania:" << endl
				<< "imie: ";
				cin >> a;
				cout << "nazwisko: ";
				cin >> b;
				cout << "indeks: ";
				cin >> c;
				cout << "Wiek: ";
				cin >> d;
				cout << "plec: ";
				cin >> e;
				database->push_back(a, b, c, d, e);
				break;
			}
			case '4': {
				database->pop_first();
				break;
			}
			default: {
                cout << endl << "Incorrect input.";
				break;
			}
		}

		cout << endl << endl << "Press any key to continue...";
        getch();
	}

	delete database;

	return 0;
}
