#include <iostream>
#include <iomanip>
#include <windows.h>
#include <ctime>
#include <string>

using namespace std;

struct element 
{
	int info;
	element* next;
	element* prev;
};

void clear();
void delay(int);
void start();
void program(element* left, element* right);
void addLeft(element*& left, element*& right, int value);
void addRight(element*& left, element*& right, int value);
element* addAfterElement(element* pointer, int value);
void EmptyList(element* &left, element* &right, int value);
int how_many_elem(element*);
void writeElements(element* left, element* right);
int which_index(element*, element*);
element* find_of_atribute(element*, int);
void deleteElem(element* &left, element* &right, element* &pointer);
void bubble_sorting(element* left, element* right, int rise_or_lees, int director);
void removeListFromMemory(element*& left);
int findTheSameValues(element* left, int value);
element* chooseElement(element* left, int value);

int main()
{
	start();
	return 0;
}

void clear() {
	system("cls");
}
void delay(int sek) {
	Sleep(sek * 1000);
}

void start() 
{
	element* left = NULL;
	element* right = NULL;
	int value = 0;

	cout << endl << endl;
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
	cout << setw(80) << "Projekt 1 - Lista liniowa dwukierunkowa" << endl << endl;
	cout << setw(69) << "Autorzy projektu:" << endl << endl;
	cout << setw(86) << "KEWIN KISIEL - 197866 i MATEUSZ KUCZEROWSKI - 197900" << endl << endl;
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
	cout << setw(73) << "PRESS ENTER TO CONTINUE: ";
	cin.ignore(); /// to mi zgarnia enterka
	delay(1);
	clear();
	program(left, right);
}

void program(element* left, element* right)
{
	int value = 0;
	int key = 0;
	element* find = NULL;

	cout << "Maksymalna wartosc elementu: 2147483647" << endl;
	cout << "0 = Wyczysc konsole." << endl;
	cout << "1 = Dodaj LEWY skrajny element listy." << endl;
	cout << "2 = Dodaj PRAWY skrajny element listy." << endl;
	cout << "3 = Wypisanie elementow listy." << endl;
	cout << "4 = Znajdz wartosc wskazana." << endl;
	cout << "5 = Dodaj element ZA elementem wskazywanym." << endl;
	cout << "6 = Usuwanie wskazywanego elementu." << endl;
	cout << "7 = Usuwanie skrajnego elementu z lewej strony." << endl;
	cout << "8 = Usuwanie skrajnego elementu z prawej strony." << endl;
	cout << "9 = Sortowanie bombelkowe." << endl;
	cout << "10 = Zwolnienie pamieci zajmowanej przez liste." << endl;
	cout << "11 = Wyjscie z konsoli." << endl;

	while (cin >> key)
	{
		switch (key)
		{
		case 0:
			clear();
			program(left, right);
			break;
		case 1:
			cout << "Podaj wartosc lewego elementu: ";
			cin >> value;
			if (value < INT_MAX) {
				addLeft(left, right, value);
			}
			else {
				std::cout << "Podano niedozwolona wartosc." << std::endl;
				cin.clear();
			}
			break;
		case 2:
			cout << "Podaj wartosc prawego elementu: ";
			cin >> value;
			if (value < INT_MAX) {
				addRight(left, right, value);
			}
			else {
				std::cout << "Podano niedozwolona wartosc." << std::endl;
				cin.clear();
			}
			break;
		case 3:
			writeElements(left, right);
			break;
		case 4:
			std::cout << "Podaj wartosc szukana: ";
			std::cin >> key;
			find = chooseElement(left, key);
			if (find != NULL) {
				std::cout << "Wskazane miejsce: " << find << " Jest to " << which_index(left, find) << " z " << how_many_elem(left) << " elementow liczac od lewej strony. " << " Wartosc w tym miejscu: " << find->info << endl;
			}
			else std::cout << "Nie znaleziono podanej wartosci!!" << std::endl;
			break;
		case 5:
			cout << "Podaj wartosc elementu ZA ktorego chcesz dodac nowy element: " << endl;
			cin >> key;
			find = chooseElement(left, key);
			if (find != NULL)
			{
				cout << "Podaj wartosc nowego elementu: " << endl;
				cin >> value;
				addAfterElement(find, value);
				cout << "Dodano nowy element!" << endl;
			}
			else cout << "Nie znaleziono podanej wartosci!!" << endl;
			break;
		case 6:
			cout << "Podaj wartosc elementu do usuniecia: " << endl;
			cin >> key;
			find = chooseElement(left, key);
			deleteElem(left, right, find);
			break;
		case 7:
			find = left;
			deleteElem(left, right, find);
			break;
		case 8:
			find = right;
			deleteElem(left, right, find);
			break;
		case 9:
			cout << "\t1 = Od lewej.\n";
			cout << "\t2 = Od prawej.\n";
			cin >> value;
			std::cout << "\t1 = Rosnaco.\n";
			std::cout << "\t2 = Malejaco.\n";
			std::cin >> key;
			bubble_sorting(left, right, key, value);
			break;
		case 10:
			removeListFromMemory(left);
			left = NULL;
			right = NULL;
			cout << "Pamiec zostala zwolniona!" << endl;
			break;
		case 11:
			removeListFromMemory(left);
			cout << "Program zostal zamkniety!" << endl;
			delay(1);
			exit(0);
			break;
		default:
			cout << "Podano nieprawidlowe dane!";
			delay(1);
			break;
		}
	}
}

void addLeft(element*& left, element*& right, int value)
{
	if (left != NULL)
	{
		element* newElement = new element;
		newElement->info = value;
		newElement->next = left;
		newElement->prev = NULL;
		if (left != NULL) left->prev = newElement;
		left = newElement;
		cout << "Dodano nowy element!" << endl;
	}
	else EmptyList(left, right, value);
}

void addRight(element*& left, element*& right, int value)
{
	if (right != NULL)
	{
		element* newElement = new element;
		newElement->info = value;
		newElement->next = NULL;
		newElement->prev = right;
		if (right != NULL) right->next = newElement;
		right = newElement;
		cout << "Dodano nowy element!" << endl;
	}
	else EmptyList(left, right, value);
}

element* addAfterElement(element* pointer, int value)
{
	if (pointer != NULL)
	{
		element* newElement = new element;
		newElement->info = value;
		newElement->next = pointer->next;
		pointer->next = newElement;
		newElement->prev = pointer;
		return newElement;
	}
}

void EmptyList(element* &left, element* &right, int value)
{
	element* newElement = new element;
	newElement->info = value;
	newElement->next = NULL;
	newElement->prev = NULL;
	left = newElement;
	right = newElement;
	cout << "Dodano nowy element!" << endl;
}

int how_many_elem(element* left) {
	if(left == NULL) return 0;
	int how_many_elem = 0;
	do
	{
		left = left->next;
		how_many_elem += 1;
	} while (left != NULL);

	return how_many_elem;
}

void writeElements(element* left, element* right)
{
	if(left == NULL)
	{
		cout << "Lista jest pusta!" << endl;
		return;
	}
	int howManyElem = how_many_elem(left);
	element* pointer = left;
	if (pointer != NULL)
	{
		int lengthInfo = 0;
		cout << "Elementy listy: " << endl;
		do {
			lengthInfo = to_string(pointer->info).length();
			cout << char(201);
			for (int j = 0; j < lengthInfo + 2; j++)
			{
				cout << char(205);
			}
			cout << char(187) << " ";
			pointer = pointer->next;
		} while (pointer != NULL);
		cout << endl;
		pointer = left;
		do
		{
			lengthInfo = to_string(pointer->info).length();
			cout << char(186) << " " << pointer->info << " " << char(186) << " ";
			pointer = pointer->next;
		} while (pointer != NULL);
		cout << endl;
		pointer = left;
		do {
			lengthInfo = to_string(pointer->info).length();
			cout << char(200);
			for (int j = 0; j < lengthInfo + 2; j++)
			{
				cout << char(205);
			}
			cout << char(188) << " ";
			pointer = pointer->next;
		} while (pointer != NULL);
		cout << endl;
		cout << "Ilosc elementow: " << howManyElem << endl;
	}
	else cout << "Lista jest pusta" << endl;
}

element* find_of_atribute(element* pointer, int find) {

	while ((pointer != NULL) and (pointer->info != find)) 
	{
		pointer = pointer->next;
	}
	if (pointer == NULL) return NULL;
	else return pointer;

}

int which_index(element* left, element* pointer) {

	int n_of_index = 1;

	while (left != pointer) {
		left = left->next;
		n_of_index++;
	}

	return n_of_index;
}

void deleteElem(element* &left, element* &right, element* &pointer)
{	
	if (pointer == NULL)
	{
		cout << "Brak elementu do usuniecia!" << endl;
		return;
	}
	if (pointer->prev != NULL and pointer->next != NULL)
	{
		pointer->prev->next = pointer->next;
		pointer->next->prev = pointer->prev;
		delete pointer;
		cout << "Usunieto wskazany element." << endl;
	}
	else if (pointer->next == NULL and pointer->prev == NULL)
	{
		right = NULL;
		left = NULL;
		delete pointer;
		cout << "Usunieto wskazany element." << endl;
	}
	else if (pointer->next == NULL)
	{
		pointer->prev->next = NULL;
		right = right->prev;
		delete pointer;
		cout << "Usunieto element z prawej strony." << endl;
	}
	else
	{
		pointer->next->prev = NULL;
		left = left->next;
		delete pointer;
		cout << "Usunieto element z lewej strony." << endl;
	}
}

void bubble_sorting(element* left, element* right, int rise_or_lees, int director)
{
	if ((rise_or_lees == 1 or rise_or_lees == 2) and (director == 1 or director == 2)) {
		int how_many = how_many_elem(left);
		int help = 0;
		element* first = NULL;
		element* pointer = NULL;
		int* sort_tab = new int[how_many];

		/// director == 1 od lewej do prawej
		if(director == 1) {
			if (rise_or_lees == 1) { ///rosnaco
				first = left;
				for (int i = 0; i < how_many; i++) { /// ilosc elementow
					left = first;
					for (int x = 1; x < how_many; x++) { /// ilosc par ilosc_elementow - 1
						pointer = left->next;
						if (left->info > pointer->info) {
							help = left->info;
							left->info = pointer->info;
							pointer->info = help;
							left = left->next;
						}
						else left = left->next;
					}
				}
			}
			else{ /// malejaco
				first = left;
				for (int i = 0; i < how_many; i++) { /// ilosc elementow
					left = first;
					for (int x = 1; x < how_many; x++) { /// ilosc par ilosc_elementow - 1
						pointer = left->next;
						if (left->info < pointer->info) {
							help = left->info;
							left->info = pointer->info;
							pointer->info = help;
							left = left->next;
						}
						else left = left->next;
					}
				}
			}
		}
		else{
			if(rise_or_lees == 1){
				first = right;
				for(int i = 0; i< how_many; i++){
					right = first;
					for(int x = 1; x< how_many; x++){
						pointer = right->prev;
						if (pointer->info > right->info) {
							help = pointer->info;
							pointer->info = right->info;
							right->info = help;
							right = right->prev;
						}
						else right = right->prev;
					}
				}
			}
			else{
				first = right;
				for (int i = 0; i < how_many; i++) {
					right = first;
					for (int x = 1; x < how_many; x++) {
						pointer = right->prev;
						if (pointer->info < right->info) {
							help = pointer->info;
							pointer->info = right->info;
							right->info = help;
							right = right->prev;
						}
						else right = right->prev;
					}
				}
			}
		}
		cout << "Posortowano liste." << endl;
	}
	else std::cout << "Podano nieprawidlowe dane!" << std::endl;
}

void removeListFromMemory(element*& left)
{
	element* pointer = NULL;
	while (left != NULL)
	{
		pointer = left;
		left = left->next;
		delete pointer;
	}
}

int findTheSameValues(element* left, int value)
{
	int sameValues = 0;
	int help = value;
	while (left != NULL)
	{
		if (help == left->info)
		{
			sameValues++;
		}
		left = left->next;
	}
	return sameValues;
}

element *chooseElement(element* left, int value)
{
	int sameValues = findTheSameValues(left, value);
	int help = 0;
	int chooseElem = 0;
	if (sameValues > 1)
	{
		cout << "W liscie znajduje sie " << sameValues << " takich samych elementow o wartosci: " << value << endl;
		cout << "Wybierz do ktorego chcesz sie odwolac patrzac od lewej strony: " << endl;
		cin >> help;
		if (help > sameValues or help < 1)
		{
			return 0;
		}
		else
		{
			while (left != NULL)
			{
				if (left->info == value)
				{
					chooseElem++;
					if (chooseElem == help)
					{
						return left;
					}
				}
				left = left->next;
			}
		}
	}
	else find_of_atribute(left, value);
}