//============================================================================
// Name        : Reversi
// Author      : Segmentation Fault
// Version     : v0.1
// Copyright   : Copyright © 2018 Segmentation Fault
// Description : Reversi - AI game
//============================================================================


#ifndef LIB_DISPLAY_H_
#define LIB_DISPLAY_H_

#include "Plansza.h"
#include <vector>

const char clear_text[] = "clear";

class Display	{

public:
	Display();
	void show_board(Board & board);
	void show_fields_on_board(Board & board);
	void show_empty_fields(std::vector <std::pair<int,int> > & cords_empty_field);
	void show_allowed_field(std::vector <std::pair<int,int> > & cords_possible_move);
	int show_color_user_pawn(int show_user_color_pawn);
	int show_mode(Board & board);
	void game_over(Board & board);
	void show_stats(Board & board);
	void clear_term();
	void showLogo();
	void loading();
	~Display();
};



#endif /* LIB_DISPLAY_H_ */
