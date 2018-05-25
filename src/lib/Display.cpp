//============================================================================
// Name        : Reversi
// Author      : Segmentation Fault
// Version     : v0.1
// Copyright   : Copyright © 2018 Segmentation Fault
// Description : Reversi - AI game
//============================================================================

#include "Plansza.h"
#include <iostream>
#include <stdlib.h>
#include "error_list.h"
#include "funkcje.h"
#include "Display.h"
#include <vector>
#include <unistd.h>

using namespace std;


//Konstruktor klasy Display dziedziczącej po klasie Board
Display::Display()
{
    //cerr << "Stworzenie pochodnej klasy Display" << endl;
}

void Display::showLogo()
{
	cout << "\x1b[1m\x1b[31m";
	cout << "______                                _   _____                         " << endl;
	cout << "| ___ \\                              (_) |  __ \\                        " << endl;
	cout << "| |_/ /  ___ __   __  ___  _ __  ___  _  | |  \\/  __ _  _ __ ___    ___ " << endl;
	cout << "|    /  / _ \\\\ \\ / / / _ \\| '__|/ __|| | | | __  / _` || '_ ` _ \\  / _ \\" << endl;
	cout << "| |\\ \\ |  __/ \\ V / |  __/| |   \\__ \\| | | |_\\ \\| (_| || | | | | ||  __/" << endl;
	cout << "\\_| \\_| \\___|  \\_/   \\___||_|   |___/|_|  \\____/ \\__,_||_| |_| |_| \\___|" << endl << endl;
	cout << "\x1b[0m";
}
void Display::loading()
{
	int i=0;
	int j=0;
	for(i=0; i<=100; i++)
	{
		clear_term();
		showLogo();
		for(j=0; j<=i; j++)
		{
			cout << ".";
		}
		cout << endl << i << "%" << endl;
		cout << "Loading, Please wait..." << endl;
		usleep(70000);
	}
	usleep(longDelay);
	clear_term();

}

//Funkcja wyświetlająca kolor pionków gracza
int Display::show_color_user_pawn(int show_user_color_pawn)
{
    if(show_user_color_pawn==BLACK_PAWN)
    {
        cout << "Jesteś Czerwonymi" << endl;
        return BLACK_PAWN;
    }
    else if(show_user_color_pawn==WHITE_PAWN)
    {
        cout << "Jesteś Zielonymi" << endl;
        return WHITE_PAWN;
    }
    else
    {
        cerr << "Ups! Coś poszło nie tak, zgłoś ten błąd" << endl;
        return BAD_COLOR;
    }
}

//Funkcja wyświetlająca tryb gry
int Display::show_mode(Board & board)
{
    if(board.game_mode == single_player)
    {
        cout << "Wybrano tryb single player" << endl;
        return single_player;
    }
    else if(board.game_mode == multiplayer)
    {
        cout << "Wybrano tryb multiplayer" << endl;
        return multiplayer;
    }
    else
    {
        cerr << "Ups! Coś poszło nie tak, zgłoś ten błąd" << endl;
        return BAD_COLOR;
    }
}


//Metoda wyświetlania planszy
void Display::show_board(Board & board)
{
    cout << "\x1b[44m  ";
    for(int position_x=1 ; position_x<=SIZE_OF_BOARD_X; position_x++)
    {
        cout << " "<< axis_label_x[position_x-1] << " ";
    }
    cout  << "  \x1b[0m" << endl;
    show_fields_on_board(board);
    cout << "\x1b[44m  ";
    for(int position_x=1 ; position_x<=SIZE_OF_BOARD_X; position_x++)
    {
        cout << " "<< axis_label_x[position_x-1] << " ";
    }
    cout  << "  \x1b[0m";
}

//Funkcja wyświetlająca po kolei wszystkie pola łącznie z zaznaczeniem obecności oraz koloru pionka
void Display::show_fields_on_board(Board & board)
{
    for(int y=1; y<=SIZE_OF_BOARD_Y; y++)
    {
        cout << "\x1b[44m" << y << " \x1b[0m";
        for(int x=1; x<=SIZE_OF_BOARD_X; x++)
        {
            switch(board.get_field(x, y))
            {
            case EMPTY_FIELD:	//Puste pole
                cout << "[ ]";
                break;
            case BLACK_PAWN:	//Pionek czarny
                cout << "[\x1b[31m\x1b[1mX\x1b[0m]";
                break;
            case WHITE_PAWN:	//Pionek biały
                cout << "[\x1b[32m\x1b[1mO\x1b[0m]";
                break;
            default:
                cout << "\x1b[47m[ ]\x1b[0m";
                break;
            }
        }
        cout << "\x1b[44m " << y << "\x1b[0m" << endl;
    }
}



//Wyświetla współrzędne wolnych pól
void Display::show_empty_fields(vector <pair<int,int> > & cords_empty_field)
{
    cout << endl << endl << "Współrzędne pustych pól: ";
    for(unsigned int i=0; i<cords_empty_field.size(); i++)
    {
        if(i%NUMBER_OF_SHOW_CORDS == REST)
        {
            cout << endl;
        }
        cout << "( ";
        switch(cords_empty_field[i].first)
        {
        case 1:
            cout << "a,";
            break;
        case 2:
            cout << "b,";
            break;
        case 3:
            cout << "c,";
            break;
        case 4:
            cout << "d,";
            break;
        case 5:
            cout << "e,";
            break;
        case 6:
            cout << "f,";
            break;
        case 7:
            cout << "g,";
            break;
        case 8:
            cout << "h,";
            break;
        default:
            break;
        }
        cout << cords_empty_field[i].second << " )";
    }
}

//Wyświetla współrzędne dozwolonych ruchów
void Display::show_allowed_field(vector <pair<int,int> > & cords_possible_move)
{
	cout << endl << endl << "Ilość możliwych ruchów: " << cords_possible_move.size();
    cout << endl << "Możliwe ruchy: " ;
    for(unsigned int i=0; i<cords_possible_move.size(); i++)
    {
        if(i%NUMBER_OF_SHOW_CORDS == REST)
        {
            cout << endl;
        }
        cout << "( ";
        switch(cords_possible_move[i].first)
        {
        case 1:
            cout << "a,";
            break;
        case 2:
            cout << "b,";
            break;
        case 3:
            cout << "c,";
            break;
        case 4:
            cout << "d,";
            break;
        case 5:
            cout << "e,";
            break;
        case 6:
            cout << "f,";
            break;
        case 7:
            cout << "g,";
            break;
        case 8:
            cout << "h,";
            break;
        default:
            break;
        }
        cout << cords_possible_move[i].second << " )";
    }
}

void Display::clear_term()
{
    if(system(clear_text) != OK)
    {
        cerr << endl << "Ekran nie został wyczyszczony !!!" << endl;
    }
}

void Display::game_over(Board & board)
{
    cout << "Koniec gry" << endl << endl;

        if(board.score_player_1 < board.score_player_2)
        {
            cout << "Wygrywa gracz grający zielonymi pionkami! Gratulacje!" << endl;
        }
        if(board.score_player_1 > board.score_player_2)
        {
            cout << "Wygrywa gracz grający czerwonymi pionkami! Gratulacje!" << endl;
        }
        else if(board.score_player_1 == board.score_player_2)
        {
            cout << "Remis! To była naprawdę wyrównana walka!" << endl;
        }

}

void Display::show_stats(Board & board)
{
    cout << endl << endl << "STATYSTYKI" << endl <<
         "Gracz czerwony " << board.score_player_1 << " - " << board.score_player_2 << "  Gracz zielony" << endl;
}

//Destruktor obiektu klasy Display
Display::~Display()
{
    //cerr << "Usunięcie pochodnej klasy Display" << endl;
}
