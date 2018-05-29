//============================================================================
// Name        : Reversi
// Author      : Segmentation Fault
// Version     : v0.1
// Copyright   : Copyright © 2018 Segmentation Fault
// Description : Reversi - AI game
//============================================================================


#ifndef LIB_PLANSZA_H_
#define LIB_PLANSZA_H_

#include <vector>
#include <algorithm>
#include "PunktyPlanszy.h"

enum {a=1,b=2,c=3,d=4,e=5,f=6,g=7,h=8};

#define SIZE_OF_BOARD_X 8	//rozmiar tablicy w wierszach
#define SIZE_OF_BOARD_Y 8	//rozmiar tablicy w kolumnach
#define EMPTY_FIELD 0	//Puste pole
#define BLACK_PAWN 1	//Pole zajęte przez pionek czarny
#define WHITE_PAWN 2	//Pole zajęte przez pionek biały
#define cord_x 4
#define cord_y 4
#define black_key '1'
#define white_key '2'
#define single_player '1'
#define multiplayer '2'
#define computer_turn_on 1
#define computer_turn_off 2
#define NUMBER_OF_SHOW_CORDS 8
#define REST 0


const char axis_label_x[8] = {'A','B','C','D','E','F','G','H'};


class Board {
	int tab[SIZE_OF_BOARD_Y][SIZE_OF_BOARD_X];

protected:

public:
	Board();	//Konstruktor
	std::vector<std::pair<int,int> >  cords_empty_field;
	std::vector<std::pair<int,int> >  cords_possible_move;
	std::vector<std::pair<int, int> > part_pawn_to_beat;
	std::vector<std::pair<int,int> >  cords_check_pawns;
	std::vector<std::pair<int,int> >  cords_simulate_moves;
	std::vector<std::pair<int,int> >  cords_second_turn;
	/*
	int evaluate_tab[SIZE_OF_BOARD_X][SIZE_OF_BOARD_Y] =
    {
        {99,  -8,  8,  6,  6,  8, -8,  99},
        {-8, -24, -4, -3, -3, -4, -24, -8},
        { 8,  -4,  7,  4,  4,  7,  -4,  8},
        { 6,  -3,  4,  0,  0,  4,  -3,  6},
        { 6,  -3,  4,  0,  0,  4,  -3,  6},
        { 8,  -4,  7,  4,  4,  7,  -4,  8},
        {-8, -24, -4, -3, -3, -4, -24, -8},
        {99,  -8,  8,  6,  6,  8, -8,  99}
    };
	*/
	int evaluate_tab[SIZE_OF_BOARD_X][SIZE_OF_BOARD_Y] =
	{
			{Corner, NearCorner, EndOfMainEdge, MainEdge, MainEdge, EndOfMainEdge, NearCorner, Corner},
			{NearCorner, SecondCorner, EndOfSecondLine, SecondMiddleLine, SecondMiddleLine, EndOfSecondLine, SecondCorner, NearCorner},
			{EndOfMainEdge, EndOfSecondLine, EndOfThirdLine, ThirdMiddleLine, ThirdMiddleLine, EndOfThirdLine, EndOfSecondLine, EndOfMainEdge},
			{MainEdge, SecondMiddleLine, ThirdMiddleLine, Middle, Middle, ThirdMiddleLine, SecondMiddleLine, MainEdge},
			{MainEdge, SecondMiddleLine, ThirdMiddleLine, Middle, Middle, ThirdMiddleLine, SecondMiddleLine, MainEdge},
			{EndOfMainEdge, EndOfSecondLine, EndOfThirdLine, ThirdMiddleLine, ThirdMiddleLine, EndOfThirdLine, EndOfSecondLine, EndOfMainEdge},
			{NearCorner, SecondCorner, EndOfSecondLine, SecondMiddleLine, SecondMiddleLine, EndOfSecondLine, SecondCorner, NearCorner},
			{Corner, NearCorner, EndOfMainEdge, MainEdge, MainEdge, EndOfMainEdge, NearCorner, Corner}
	};

    int cords_best_move[2];
    int simulate_cords[2];
    int number_of_best_move;
	int numberOfAllowedMoves;
	int user_color_pawn;
	int computer_color_pawn;
	int depth_of_search;
	int computer_turn;
	char game_mode;
	int BAD_MOVE;
	int score_player_1;
	int score_player_2;
	void choose_mode();
	void clear_board();
	void set_main_pawns();
	void set_color_user_pawn();
	int set_pawn_on_field(int x, int y, int color_of_pawn);
	int get_field(int x, int y);
	int change_pawn_on_field(int x, int y, int color_of_pawn);
	void change_player();
	void whose_move();
	int show_user_color_pawn();
	~Board();	//Destruktor
};



#endif /* LIB_PLANSZA_H_ */
