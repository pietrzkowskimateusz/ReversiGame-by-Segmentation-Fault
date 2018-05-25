//============================================================================
// Name        : Reversi
// Author      : Segmentation Fault
// Version     : v0.1
// Copyright   : Copyright © 2018 Segmentation Fault
// Description : Reversi - AI game
//============================================================================

#include <iostream>
#include "lib/Plansza.h"
#include "lib/Menu.h"
#include "lib/Zmienne.h"
#include "lib/funkcje.h"
#include <stdlib.h>
#include "lib/Display.h"
#include "lib/Algorithm.h"


using namespace std;


int main()
{
	Board board;
	Algorithm algorithm;
	Display display;
	display.clear_term();
	display.loading();
	Menu menu;

	while(pressed_key != EXIT)
	{

		menu.show_menu();
		cin >> pressed_key;

		switch (pressed_key)
		{
			//Rozpoczęcie gry
			case '1':
				GAME = true;
				display.clear_term();
				clear_bufor();
				board.clear_board();
				algorithm.clear_vectors(board);
				algorithm.clear_cords_simulate_moves(board);
				board.set_main_pawns();
                board.set_color_user_pawn();
                display.clear_term();
                while(GAME)
                {

                	algorithm.make_stats(board);
                	display.show_board(board);
                	display.show_stats(board);
                	algorithm.search_empty_fields(board);
                	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
                	algorithm.clear_part_pawn_to_beat(board);
                	algorithm.clear_cords_check_pawns(board);
                	display.show_allowed_field(board.cords_possible_move);
                	//algorithm.search_best_move(board);
                	if(algorithm.setting_user_pawn_on_field(board))
                	{
                		GAME = false;
                		display.game_over(board);
               		}
                	else
                	{

                		algorithm.clear_vectors(board);
                		algorithm.clear_cords_simulate_moves(board);
                		board.change_player();
                		display.clear_term();
                	}
                }
                break;

            //Wybranie koloru pionków
			case '2':
				display.clear_term();
				clear_bufor();
				board.set_color_user_pawn();
				display.clear_term();
				display.show_color_user_pawn(board.show_user_color_pawn());
				break;
				//Wybranie trybu gry
			case '3':
				display.clear_term();
				clear_bufor();
				board.choose_mode();
				display.clear_term();
				display.show_mode(board);
				break;


			//Wybranie poziomu trudności
			case '4':
				display.clear_term();
				clear_bufor();
				cout << "OPCJA CHWILOWO NIEDOSTĘPNA" << endl << endl;
				break;


			//Wyświetlenie zasad gry
			case '5':
				display.clear_term();
				clear_bufor();
				menu.show_rules();
				cout << endl << endl;
				//cout << "OPCJA CHWILOWO NIEDOSTĘPNA" << endl;
				break;


			//Wyjście z gry
			case '0':
				display.clear_term();
				clear_bufor();
				return EXIT;
				break;

			default:
				display.clear_term();
				clear_bufor();
				cout << "Nieprawidłowy wybór" << endl << endl;
		}
	}
}
