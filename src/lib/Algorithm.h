//============================================================================
// Name        : Reversi
// Author      : Segmentation Fault
// Version     : v0.1
// Copyright   : Copyright © 2018 Segmentation Fault
// Description : Reversi - AI game
//============================================================================

#ifndef LIB_ALGORITHM_H_
#define LIB_ALGORITHM_H_

#include "Plansza.h"
#include "Display.h"

//Kierunki świata
#define N -1
#define E 1
#define S 1
#define W -1


class Algorithm {
public:
	Algorithm();
	int setting_user_pawn_on_field(Board & board);
	int search_empty_fields(Board & board);
	void clear_cords_empty_field(Board & board);
	void clear_cords_possible_move(Board & board);
	void clear_part_pawn_to_beat(Board & board);
	void clear_cords_check_pawns(Board & board);
	void clear_cords_simulate_moves(Board & board);
	void clear_vectors(Board & board);
	int make_best_move(Board & board);
	void simulate_moves(Board & board);
	int make_beat(Board & board, int x, int y);
	int make_stats(Board & board);
	int search_best_move(Board & board);
	void search_best_move2(Board & board, Board & copy_of_board);
	void search_worst_move(Board & board);
	int search_allowed_fields(Board & board);
	int min_move_value(Board & board);
    int check_field(Board & board, int x, int y, int shift_x, int shift_y);
    bool LackOfMoveBlack;
    bool LackOfMoveWhite;
    ~Algorithm();
};

#endif
