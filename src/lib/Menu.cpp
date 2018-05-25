//============================================================================
// Name        : Reversi
// Author      : Segmentation Fault
// Version     : v0.1
// Copyright   : Copyright © 2018 Segmentation Fault
// Description : Reversi - AI game
//============================================================================


#include "Menu.h"
#include <iostream>

using namespace std;



Menu::Menu()
{
    cout << "Witaj w grze Reversi stworzonej prze zespół Segmentation Fault" << endl;
}



void Menu::show_menu()
{
    cout << endl <<
         "1. Rozpocznij nową grę" << endl <<
         "2. Wybór koloru pionków" << endl <<
         "3. Wybór trybu gry(domyślnie single player)" << endl <<
         "4. Wybierz poziom trudności" << endl <<
         "5. Zasady gry" << endl <<
         "0. Koniec gry" << endl <<
         " TWÓJ WYBÓR: ";
}


void Menu::show_rules()
{
    cout << "Gra rozgrywana na planszy 8x8 pól. " << endl <<
         "Każdy z dwóch graczy ma do dyspozycji pionki: jeden koloru białego, drugi - czarnego. " << endl <<
         "Początkowo na planszy znajdują się po dwa pionki każdego z graczy, " << endl <<
         "ułożone na środku naprzeciw sobie po ukosie. Gracze układają na przemian pionki " << endl <<
         "własnego koloru na wolnych polach planszy do momentu, aż plansza zostanie " << endl <<
         "całkowicie zapełniona lub żaden z graczy nie będzie mógł wykonać dozwolonego ruchu. " << endl <<
         "Dozwolony ruch to taki, w którym pionek jest ułożony na polu, które " << endl <<
         "znajduje się w linii (poziomej, pionowej lub ukośnej) z innym pionkiem gracza " << endl <<
         "wykonującego ruch, i na dokładnie wszystkich polach pomiędzy wybranym polem a tym " << endl <<
         "pionkiem znajdują się pionki przeciwnika. Te pionki zostają po wykonaniu ruchu " << endl <<
         "przejęte i zmieniają kolor na przeciwny (tzn. na kolor pionków gracza, który " << endl <<
         "wykonuje ruch). W jednym ruchu można przejmować pionki na więcej niż jednej linii. " << endl <<
         "Jeśli gracz nie może wykonać dozwolonego ruchu, traci automatycznie kolejkę. " << endl <<
         "Wygrywa ten z graczy, którego większa liczba pionków znajduje się na planszy " << endl <<
         "po zakończeniu gry; jeśli liczba pionków graczy jest jednakowa, następuje remis." << endl << endl;
}



Menu::~Menu()
{

}


