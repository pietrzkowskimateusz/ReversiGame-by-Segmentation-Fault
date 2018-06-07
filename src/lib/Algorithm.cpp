//============================================================================
// Name        : Reversi
// Author      : Segmentation Fault
// Version     : v0.1
// Copyright   : Copyright © 2018 Segmentation Fault
// Description : Reversi - AI game
//============================================================================

#include <iostream>
#include "Algorithm.h"
#include "funkcje.h"
#include "error_list.h"
#include <unistd.h>
#include "Display.h"

using namespace std;

Algorithm::Algorithm()
{
    LackOfMoveBlack = false;
    LackOfMoveWhite = false;
}

int Algorithm::setting_user_pawn_on_field(Board & board)
{
    int x, y;			//pojedyncze współrzędne pionka
    char XY_cord[2];	//pełne wspolrzedne pionka podawane przez użytkownika
    board.whose_move();


    if(board.game_mode == single_player && board.computer_turn == computer_turn_on) // w trybie single player
    {
        //Plansza zapełniona - Tradycyjny koniec gry
        if(board.cords_empty_field.empty() || (LackOfMoveBlack && LackOfMoveWhite))
        {
            return 1;
        }
        cout << "Myślę..." << endl;
        usleep(longDelay);
        make_best_move(board);
    }
    else if(board.computer_turn == computer_turn_off)
    {
        if(!board.cords_possible_move.empty())
        {
            LackOfMoveBlack = false;
            LackOfMoveWhite = false;

            do
            {
                cout << endl << "Podaj gdzie chcesz umieścić pionek, aby wyjść wpisz 0 i zatwierdź klawiszem Enter: ";
                cin >> XY_cord;
                switch(XY_cord[0])
                {
                case 'a':
                    x = a;
                    break;
                case 'b':
                    x = b;
                    break;
                case 'c':
                    x = c;
                    break;
                case 'd':
                    x = d;
                    break;
                case 'e':
                    x = e;
                    break;
                case 'f':
                    x = f;
                    break;
                case 'g':
                    x = g;
                    break;
                case 'h':
                    x = h;
                    break;
                case '0':
                    x = Esc;
                    break;
                default:
                    x=0;
                    break;
                }
                switch(XY_cord[1])
                {
                case '1':
                    y = 1;
                    break;
                case '2':
                    y = 2;
                    break;
                case '3':
                    y = 3;
                    break;
                case '4':
                    y = 4;
                    break;
                case '5':
                    y = 5;
                    break;
                case '6':
                    y = 6;
                    break;
                case '7':
                    y = 7;
                    break;
                case '8':
                    y = 8;
                    break;
                default:
                    y=0;
                    break;
                }
                clear_bufor();
                //Wyjście z gry
                if(x == Esc)
                {
                    return 1;
                }
            }
            while(board.set_pawn_on_field(x, y, board.user_color_pawn) != OK);
            make_beat(board,x,y);
        }
        else if(board.cords_possible_move.empty()) //jeśli nie ma ruchów zmień kolejkę
        {
            cout << endl << "Tracisz kolejkę" << endl;
            usleep(longDelay);
            LackOfMoveBlack = true;
            board.BAD_MOVE = 0;
        }
    }
    return 0;
}


//Funkcja wyszukująca puste pola
int Algorithm::search_empty_fields(Board & board)
{
    for(int y=1; y<=SIZE_OF_BOARD_Y; y++)
    {
        for(int x=1; x<=SIZE_OF_BOARD_X; x++)
        {
            if(board.get_field(x,y) == EMPTY_FIELD)
            {
                board.cords_empty_field.push_back(make_pair(x,y));
            }
        }
    }
    return board.cords_empty_field.size();
}

//Funkcja sprawdza ile jest pól danego koloru
int Algorithm::make_stats(Board & board)
{
    board.score_player_1 = 0;
    board.score_player_2 = 0;

    for(int y=1; y<=SIZE_OF_BOARD_Y; y++)
    {
        for(int x=1; x<=SIZE_OF_BOARD_X; x++)
        {
            if(board.get_field(x,y) == BLACK_PAWN)
            {
                board.score_player_1++;
            }
        }
    }

    for(int y=1; y<=SIZE_OF_BOARD_Y; y++)
    {
        for(int x=1; x<=SIZE_OF_BOARD_X; x++)
        {
            if(board.get_field(x,y) == WHITE_PAWN)
            {
                board.score_player_2++;
            }
        }
    }
    return board.score_player_1;
}

//Funkcja wykonująca najlepszy ruch
int Algorithm::make_best_move(Board & board)
{
    //Display display;

    simulate_moves(board);
    if(!board.cords_possible_move.empty())
    {
        LackOfMoveBlack = false;
        LackOfMoveWhite = false;
        cout << "Ruch komputera: ";
        switch(board.cords_best_move[0])
        {
        case 1:
        	cout << "a";
        	break;
        case 2:
        	cout << "b";
        	break;
        case 3:
        	cout << "c";
        	break;
        case 4:
        	cout << "d";
        	break;
        case 5:
        	cout << "e";
        	break;
        case 6:
        	cout << "f";
        	break;
        case 7:
        	cout << "g";
        	break;
        case 8:
        	cout << "h";
        	break;
        default:
        	cout << "BŁĄD ";
        	break;
        }
        cout << board.cords_best_move[1] << endl << endl;
        board.set_pawn_on_field(board.cords_best_move[0], board.cords_best_move[1], board.user_color_pawn);
        make_beat(board, board.cords_best_move[0], board.cords_best_move[1]);
        return 0;
    }
    else if(board.cords_possible_move.empty()) //jeśli nie ma ruchów zmień kolejkę
    {
        LackOfMoveWhite = true;
        board.BAD_MOVE = 0;
        cout << endl << "Tracisz kolejkę" << endl;
        usleep(longDelay);
        return 1;
    }
    return 1;
}

//Funkcja wyszukująca najlepszego ruchu na podstawie wartości pól
int Algorithm::search_best_move(Board & board)
{
    int maxi;
    maxi = board.evaluate_tab[board.cords_possible_move[0].first-1][board.cords_possible_move[0].second-1];
    board.cords_best_move[0] = board.cords_possible_move[0].first;
    board.cords_best_move[1] = board.cords_possible_move[0].second;

    for(unsigned int i=0; i<board.cords_possible_move.size(); i++)
    {
        if(board.evaluate_tab[board.cords_possible_move[i].first][board.cords_possible_move[0].second] >= maxi)
        {
            maxi = board.evaluate_tab[board.cords_possible_move[i].first-1][board.cords_possible_move[i].second-1];
            board.cords_best_move[0] = board.cords_possible_move[i].first;
            board.cords_best_move[1] = board.cords_possible_move[i].second;
        }
    }
    return OK;
}


void Algorithm::search_best_move2(Board & board,Board & copy_of_board)
{
    int maxi;
    maxi = copy_of_board.evaluate_tab[copy_of_board.cords_possible_move[0].first-1][copy_of_board.cords_possible_move[0].second-1];
    copy_of_board.simulate_cords[0] = copy_of_board.cords_possible_move[0].first;
    copy_of_board.simulate_cords[1] = copy_of_board.cords_possible_move[0].second;

    for(unsigned int i=0; i<copy_of_board.cords_possible_move.size(); i++)
    {
        if(copy_of_board.evaluate_tab[copy_of_board.cords_possible_move[i].first][copy_of_board.cords_possible_move[0].second] >= maxi)
        {
            maxi = copy_of_board.evaluate_tab[copy_of_board.cords_possible_move[i].first-1][copy_of_board.cords_possible_move[i].second-1];
            copy_of_board.simulate_cords[0] = copy_of_board.cords_possible_move[i].first;
            copy_of_board.simulate_cords[1] = copy_of_board.cords_possible_move[i].second;
        }
    }
    board.cords_simulate_moves.push_back(make_pair(copy_of_board.simulate_cords[0],copy_of_board.simulate_cords[1]));
}

void Algorithm::search_worst_move(Board & board, Board & copy_of_board)
{
    int mini;
    mini = copy_of_board.evaluate_tab[copy_of_board.cords_possible_move[0].first-1][copy_of_board.cords_possible_move[0].second-1];
    copy_of_board.simulate_cords[0] = copy_of_board.cords_possible_move[0].first;
    copy_of_board.simulate_cords[1] = copy_of_board.cords_possible_move[0].second;

    for(unsigned int i=0; i<copy_of_board.cords_possible_move.size(); i++)
    {
        if(copy_of_board.evaluate_tab[copy_of_board.cords_possible_move[i].first][copy_of_board.cords_possible_move[0].second] >= mini)
        {
            mini = copy_of_board.evaluate_tab[copy_of_board.cords_possible_move[i].first-1][copy_of_board.cords_possible_move[i].second-1];
            copy_of_board.simulate_cords[0] = copy_of_board.cords_possible_move[i].first;
            copy_of_board.simulate_cords[1] = copy_of_board.cords_possible_move[i].second;
        }
    }
    board.cords_second_turn.push_back(make_pair(copy_of_board.simulate_cords[0],copy_of_board.simulate_cords[1]));
}

int Algorithm::min_move_value(Board & board)
{
    int sum, sum_2;

    sum = board.evaluate_tab[board.cords_possible_move[0].first-1][board.cords_possible_move[0].second-1]
    - board.evaluate_tab[board.cords_second_turn[0].first-1][board.cords_second_turn[0].second-1]
    + board.evaluate_tab[board.cords_simulate_moves[0].first-1][board.cords_simulate_moves[0].second-1];

    for(unsigned int i=0; i<board.cords_simulate_moves.size(); i++)
    {
    sum_2 = board.evaluate_tab[board.cords_possible_move[i].first-1][board.cords_possible_move[i].second-1]
     - board.evaluate_tab[board.cords_second_turn[i].first-1][board.cords_second_turn[i].second-1]
    + board.evaluate_tab[board.cords_simulate_moves[i].first-1][board.cords_simulate_moves[i].second-1];
        if(sum_2 >= sum)
        {
           sum = board.evaluate_tab[board.cords_possible_move[i].first-1][board.cords_possible_move[i].second-1]
            - board.evaluate_tab[board.cords_second_turn[i].first-1][board.cords_second_turn[i].second-1]
            + board.evaluate_tab[board.cords_simulate_moves[i].first-1][board.cords_simulate_moves[i].second-1];
            board.number_of_best_move = i;
        }
    }
    return 1;
}

//Funkcja symulujące dalsze ruchy
void Algorithm::simulate_moves(Board & board)
{
    Board copy_of_board;

    for(unsigned int i=0; i<board.cords_possible_move.size(); i++)
    {
        copy_of_board = board;
        //display.show_board(copy_of_board);
        search_empty_fields(copy_of_board);
        copy_of_board.numberOfAllowedMoves=search_allowed_fields(copy_of_board);
        clear_part_pawn_to_beat(copy_of_board);
        clear_cords_check_pawns(copy_of_board);
        //display.show_allowed_field(copy_of_board.cords_possible_move);
        copy_of_board.set_pawn_on_field(copy_of_board.cords_possible_move[i].first,copy_of_board.cords_possible_move[i].second,copy_of_board.user_color_pawn);
        make_beat(copy_of_board,copy_of_board.cords_possible_move[i].first,copy_of_board.cords_possible_move[i].second);
        clear_vectors(copy_of_board);
        copy_of_board.change_player();

        for(int j=1; j<3; j++)
        {
            //display.show_board(copy_of_board);
            search_empty_fields(copy_of_board);
            copy_of_board.numberOfAllowedMoves=search_allowed_fields(copy_of_board);
            clear_part_pawn_to_beat(copy_of_board);
            clear_cords_check_pawns(copy_of_board);
            //display.show_allowed_field(copy_of_board.cords_possible_move);

            if(j%2==0)
            {
                search_best_move2(board,copy_of_board);
            }
            else if(j%2==1)
                search_worst_move(board, copy_of_board);

            copy_of_board.set_pawn_on_field(copy_of_board.simulate_cords[0], copy_of_board.simulate_cords[1], copy_of_board.user_color_pawn);
            make_beat(copy_of_board,copy_of_board.simulate_cords[0], copy_of_board.simulate_cords[1]);
            clear_vectors(copy_of_board);
            copy_of_board.change_player();
            //display.show_board(copy_of_board);
        }

    }
    min_move_value(board);
    board.cords_best_move[0] = board.cords_possible_move[board.number_of_best_move].first;
    board.cords_best_move[1] = board.cords_possible_move[board.number_of_best_move].second;
}


//Funkcja czyszcząca vector cords_empty_field
void Algorithm::clear_cords_empty_field(Board & board)
{
    board.cords_empty_field.clear();
}

void Algorithm::clear_cords_possible_move(Board & board)
{
    board.cords_possible_move.clear();
}

void Algorithm::clear_part_pawn_to_beat(Board & board)
{
    board.part_pawn_to_beat.clear();
}

void Algorithm::clear_cords_check_pawns(Board & board)
{
    board.cords_check_pawns.clear();
}

void Algorithm::clear_cords_simulate_moves(Board & board)
{
    board.cords_simulate_moves.clear();
}

void Algorithm::clear_vectors(Board & board)
{
    clear_cords_empty_field(board);
    clear_cords_possible_move(board);
    clear_part_pawn_to_beat(board);
    clear_cords_check_pawns(board);
}

//Funkcja wykonująca zmianę koloru zbitych pionków
int Algorithm::make_beat(Board & board,int x, int y)
{
    check_field(board,x,y,0,N);        //sprawdzanie które pola można zbić
    check_field(board,x,y,0,S);
    check_field(board,x,y,E,N);
    check_field(board,x,y,E,S);
    check_field(board,x,y,E,0);
    check_field(board,x,y,W,0);
    check_field(board,x,y,W,N);
    check_field(board,x,y,W,S);

    for(unsigned int i=0; i<board.part_pawn_to_beat.size(); i++)
    {
        board.change_pawn_on_field(board.part_pawn_to_beat[i].first, board.part_pawn_to_beat[i].second, board.user_color_pawn);
    }
    return board.part_pawn_to_beat.size();
}


//Funkcja szuka dozwolonych ruchów na całej planszy
int Algorithm::search_allowed_fields(Board & board)
{
    for(unsigned int i=0; i<board.cords_empty_field.size(); i++)
    {
        check_field(board,board.cords_empty_field[i].first,board.cords_empty_field[i].second,0,N);
        check_field(board,board.cords_empty_field[i].first,board.cords_empty_field[i].second,0,S);
        check_field(board,board.cords_empty_field[i].first,board.cords_empty_field[i].second,E,N);
        check_field(board,board.cords_empty_field[i].first,board.cords_empty_field[i].second,E,S);
        check_field(board,board.cords_empty_field[i].first,board.cords_empty_field[i].second,E,0);
        check_field(board,board.cords_empty_field[i].first,board.cords_empty_field[i].second,W,0);
        check_field(board,board.cords_empty_field[i].first,board.cords_empty_field[i].second,W,N);
        check_field(board,board.cords_empty_field[i].first,board.cords_empty_field[i].second,W,S);
    }
    return board.cords_possible_move.size();
}


int Algorithm::check_field(Board & board, int x, int y, int shift_x, int shift_y)
{
    int i=0;
    int add_x1, add_x2, add_y1, add_y2;
    while(i<8)
    {
        if(shift_x==0)
        {
            add_x1 = 0;
            add_x2 = 0;
        }
        else if(shift_x>0)
        {
            add_x1 = 1;
            add_x2 = 2;
        }
        else if(shift_x<0)
        {
            add_x1 = -1;
            add_x2 = -2;
        }

        if(shift_y==0)
        {
            add_y1 = 0;
            add_y2 = 0;
        }
        else if(shift_y>0)
        {
            add_y1 = 1;
            add_y2 = 2;
        }
        else if(shift_y<0)
        {
            add_y1 = -1;
            add_y2 = -2;
        }

        if(board.user_color_pawn == BLACK_PAWN)	 //Pętla gdy ruch ma wykonywać pionek czarny
        {
            if(board.get_field(x+shift_x, y+shift_y) == WHITE_PAWN && board.get_field(x+(shift_x+add_x1), y+(shift_y+add_y1)) == BLACK_PAWN)
            {
                for(unsigned int i=0; i<board.cords_check_pawns.size(); i++)
                {
                    board.part_pawn_to_beat.push_back(make_pair(board.cords_check_pawns[i].first,board.cords_check_pawns[i].second));
                }

                board.part_pawn_to_beat.push_back(make_pair(x+shift_x,y+shift_y));

                bool pair = false;
                for(unsigned int i=0; i<board.cords_possible_move.size(); i++)
                {
                    if(x==board.cords_possible_move[i].first && y==board.cords_possible_move[i].second)
                    {
                        pair=true;
                    }
                }
                if(pair==false)
                {
                    board.cords_possible_move.push_back(make_pair(x,y));
                }
                return POSSIBLE_MOVE;
            }
            else if(board.get_field(x+shift_x, y+shift_y) == WHITE_PAWN && board.get_field(x+(shift_x+add_x1), y+(shift_y+add_y1)) == WHITE_PAWN && board.get_field(x+(shift_x+add_x2), y+(shift_y+add_y2)) !=EMPTY_FIELD)
            {
                board.cords_check_pawns.push_back(make_pair(x+shift_x,y+shift_y));

                if(shift_x < 0)
                    shift_x--;
                else if(shift_x > 0)
                    shift_x++;

                if(shift_y < 0)
                    shift_y--;
                else if(shift_y > 0)
                    shift_y++;
            }
            else if(board.get_field(x+shift_x, y+shift_y) == EMPTY_FIELD)
            {
                return UNPOSSIBLE_MOVE;
            }
        }


        else if(board.user_color_pawn == WHITE_PAWN)	//Pętla gdy ruch ma wykonywać pionek biały
        {
            if(board.get_field(x+shift_x, y+shift_y) == BLACK_PAWN && board.get_field(x+(shift_x+add_x1), y+(shift_y+add_y1)) == WHITE_PAWN)
            {
                for(unsigned int i=0; i<board.cords_check_pawns.size(); i++)
                {
                    board.part_pawn_to_beat.push_back(make_pair(board.cords_check_pawns[i].first,board.cords_check_pawns[i].second));
                }

                board.part_pawn_to_beat.push_back(make_pair(x+shift_x,y+shift_y));
                bool pair = false;
                for(unsigned int i=0; i<board.cords_possible_move.size(); i++)
                {
                    if(x==board.cords_possible_move[i].first && y==board.cords_possible_move[i].second)
                    {
                        pair=true;
                    }
                }
                if(pair==false)
                {
                    board.cords_possible_move.push_back(make_pair(x,y));
                }
                return POSSIBLE_MOVE;
            }
            else if(board.get_field(x+shift_x, y+shift_y) == BLACK_PAWN && board.get_field(x+(shift_x+add_x1), y+(shift_y+add_y1)) == BLACK_PAWN && board.get_field(x+(shift_x+add_x2), y+(shift_y+add_y2)) !=EMPTY_FIELD)
            {
                board.cords_check_pawns.push_back(make_pair(x+shift_x,y+shift_y));

                if(shift_x < 0)
                    shift_x--;
                else if(shift_x > 0)
                    shift_x++;

                if(shift_y < 0)
                    shift_y--;
                else if(shift_y > 0)
                    shift_y++;
            }
            else if(board.get_field(x+shift_x, y+shift_y) == EMPTY_FIELD)
            {
                return UNPOSSIBLE_MOVE;
            }
        }
        i++;
    }
    clear_cords_check_pawns(board);
    return UNPOSSIBLE_MOVE;

}

Algorithm::~Algorithm()
{

}

