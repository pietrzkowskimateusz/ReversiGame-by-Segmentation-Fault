//============================================================================
// Name        : Reversi
// Author      : Segmentation Fault
// Version     : v0.1
// Copyright   : Copyright © 2018 Segmentation Fault
// Description : Reversi - AI game
//============================================================================


#include "Plansza.h"
#include <iostream>
#include "error_list.h"
#include "funkcje.h"

using namespace std;


//Konstruktor obiektu klasy Plansza
Board::Board()
{
    user_color_pawn = BLACK_PAWN;	//Domyślnie ustaw kolor pionków gracza na czarny
    computer_color_pawn = WHITE_PAWN;
    BAD_MOVE = 0;
    computer_turn = 2;
    numberOfAllowedMoves=0;
    depth_of_search = 2;
    game_mode = '1';
    score_player_1 = 0;
    score_player_2 = 0;
    number_of_best_move = 0;
    //cerr << "Stworzenie klasy bazowej Board" << endl;
}




//Metoda ustawiania pionków na planszy
int Board::set_pawn_on_field(int x, int y, int color_of_pawn)
{

    if((x >= 1 && x <= SIZE_OF_BOARD_X) && (y >= 1 && y <= SIZE_OF_BOARD_Y))
    {
        if(get_field(x,y) == EMPTY_FIELD)
        {
            for(int i=0; i<numberOfAllowedMoves; i++)
            {
                if(x == cords_possible_move[i].first && y == cords_possible_move[i].second)
                {
                    tab[y-1][x-1] = color_of_pawn;
                    BAD_MOVE = 0;
                    return OK;
                }
            }


            cout << "Wybrano niedozwolone miejsce!" << endl;
            BAD_MOVE = 1;
            return BAD_CORD;
        }
        else
        {
            cout << "To pole jest już zajęte!" << endl;
            BAD_MOVE = 1;
            return BAD_CORD;
        }
    }
    else
    {
        cout << "Wybrano miejsce spoza planszy!" << endl;
        BAD_MOVE = 1;
        return BAD_CORD;
    }
}



void Board::whose_move()
{
    if(user_color_pawn==BLACK_PAWN)
        cout << endl << endl << "Ruch wykonuje czerwony pionek." << endl;
    else if(user_color_pawn==WHITE_PAWN)
        cout << endl << endl <<  "Ruch wykonuje zielony pionek." << endl;
    else
        cerr << "Ups! Coś poszło nie tak, zgłoś ten błąd, whose" << endl;
}


//Metoda zwracająca wartość pola na planszy
int Board::get_field(int x, int y)
{
    if((x >= 1 && x <= SIZE_OF_BOARD_X) && (y >= 1 && y <= SIZE_OF_BOARD_Y))
    {
        return tab[y-1][x-1];
    }
    else
    {
        return BAD_CORD;
    }
}



int Board::change_pawn_on_field(int x, int y, int color_of_pawn)
{
    if(color_of_pawn == BLACK_PAWN)
    {
        tab[y-1][x-1] = BLACK_PAWN;
        return BLACK_PAWN;
    }
    else if(color_of_pawn == WHITE_PAWN)
    {
        tab[y-1][x-1] = WHITE_PAWN;
        return WHITE_PAWN;
    }
    return BAD_COLOR;
}


//Funkcja wyboru koloru pionka gracza
void Board::set_color_user_pawn()
{
    char pressed_char;	//zmienna przechowywująca wartość wpisanego znaku
    bool color_correct = false;		//zmienna pomocnicza służąca do określania, czy wprowadzony kolor jest poprawny
    while(!color_correct)
    {
        cout << endl << "Wybierz 1 jeśli chcesz być czerwonymi pionkami lub 2 jeśli chcesz być zielonymi" << endl <<
             " TWÓJ WYBÓR: ";
        cin >> pressed_char;
        if(pressed_char==black_key)
        {
            clear_bufor();
            user_color_pawn = BLACK_PAWN;
            computer_color_pawn = WHITE_PAWN;
            color_correct = true;
        }
        else if	(pressed_char==white_key)
        {
            clear_bufor();
            user_color_pawn = WHITE_PAWN;
            computer_color_pawn = BLACK_PAWN;
            color_correct = true;
        }
        else
        {
            clear_bufor();
            cout << "Błędny wybór" << endl << "Powtórz wybór" << endl;
            color_correct = false;
        }
    }
}

//Funkcja wyboru koloru pionka gracza
void Board::choose_mode()
{
    char pressed_char;	//zmienna przechowywująca wartość wpisanego znaku
    bool mode_correct = false;		//zmienna pomocnicza służąca do określania, czy wprowadzony kolor jest poprawny
    while(!mode_correct)
    {
        cout << endl << "Wybierz tryb gry: 1 jeśli chcesz wybrać tryb single player lub 2 jeśli chcesz wybrać tryb two player" << endl <<
             " TWÓJ WYBÓR: ";
        cin >> pressed_char;
        if(pressed_char==single_player)
        {
            clear_bufor();
            game_mode = single_player;
            mode_correct = true;
        }
        else if	(pressed_char==multiplayer)
        {
            clear_bufor();
            game_mode = multiplayer;
            mode_correct = true;
        }
        else
        {
            clear_bufor();
            cout << "Błędny wybór" << endl << "Powtórz wybór" << endl;
            mode_correct = false;
        }
    }
}


//Funkcja ustawiania pionki w polach bazowych
void Board::set_main_pawns()
{
    tab[cord_y][cord_x] = WHITE_PAWN;
    tab[cord_y][cord_x-1] = BLACK_PAWN;
    tab[cord_y-1][cord_x] = BLACK_PAWN;
    tab[cord_y-1][cord_x-1] = WHITE_PAWN;
}



//Czyść planszę
void Board::clear_board()
{
    //Czyszczenie tablicy
    for(int y=1; y<=SIZE_OF_BOARD_Y; y++)
    {
        for(int x=1; x<=SIZE_OF_BOARD_X; x++)
        {
            tab[y-1][x-1] = EMPTY_FIELD;	//Ustawienie w każdym polu 0
        }
    }
}


//Funkcja do zmiany zawodnika po wykonaniu prawidłowego ruchu
void Board::change_player()
{
    if(BAD_MOVE==0)
    {
        if(game_mode == single_player)
        {
            if(user_color_pawn == BLACK_PAWN)
            {
                if(computer_turn == computer_turn_off)
                    computer_turn = computer_turn_on;
                else if(computer_turn == computer_turn_on)
                    computer_turn = computer_turn_off;
                user_color_pawn = WHITE_PAWN;
            }
            else if(user_color_pawn == WHITE_PAWN)
            {
                if(computer_turn == computer_turn_off)
                    computer_turn = computer_turn_on;
                else if(computer_turn == computer_turn_on)
                    computer_turn = computer_turn_off;
                user_color_pawn = BLACK_PAWN;
            }
        }
        else
        {
            if(user_color_pawn == BLACK_PAWN)
            {
                user_color_pawn = WHITE_PAWN;
            }
            else if(user_color_pawn == WHITE_PAWN)
            {
                user_color_pawn = BLACK_PAWN;
            }
        }
    }
    else if(BAD_MOVE==1)
        cerr << "Spróbuj jeszcze raz." << endl;
        else cerr << "Ups! Coś poszło nie tak, zgłoś ten błąd, whose" << endl;

}



int Board::show_user_color_pawn()
{
    return user_color_pawn;
}

//Destruktor obiektu klasy Plansza
Board::~Board()
{
    //cerr << "Usunięta klasa bazowa Board" << endl;
}



