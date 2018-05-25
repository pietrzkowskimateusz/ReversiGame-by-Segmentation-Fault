#include <iostream>
#include <gtest/gtest.h>
#include "../../src/lib/Plansza.h"
#include "../../src/lib/Algorithm.h"
#include "valueTest.h"


using namespace std;


TEST(BoardTest, setPawnOnPossibleField)
{
	Board board;
	Algorithm algorithm;
	board.user_color_pawn=BlackPawn;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
	EXPECT_EQ(board.set_pawn_on_field(cord_X, cord_Y, BlackPawn), OK);
}

TEST(BoardTest, setPawnOnImpossibleField)
{
	Board board;
	Algorithm algorithm;
	board.user_color_pawn=BlackPawn;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
	EXPECT_NE(board.set_pawn_on_field(cord_X+1, cord_Y, BlackPawn), OK);
}

TEST(BoardTest, getEmptyField)
{
	Board board;
	board.clear_board();
	EXPECT_EQ(board.get_field(cord_X, cord_Y), EmptyField);
}

TEST(BoardTest, getBlackField)
{
	Board board;
	board.clear_board();
	board.set_main_pawns();
	EXPECT_EQ(board.get_field(4, 4), BlackPawn);
}

TEST(BoardTest, showGoodColorUserPawn)
{
	Board board;
	board.user_color_pawn = BlackPawn;
	EXPECT_EQ(board.show_user_color_pawn(), BlackPawn);
}

TEST(BoardTest, showBadColorUserPawn)
{
	Board board;
	board.user_color_pawn = BlackPawn;
	EXPECT_NE(board.show_user_color_pawn(), WhitePawn);
}

TEST(BoardTest, goodChangePawnOnField)
{
	Board board;
	Algorithm algorithm;
	board.user_color_pawn=BlackPawn;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
	board.set_pawn_on_field(cord_X,cord_Y,BlackPawn);
	EXPECT_EQ(board.change_pawn_on_field(cord_X, cord_Y, WhitePawn), WhitePawn);
}

TEST(BoardTest, badChangePawnOnField)
{
	Board board;
	Algorithm algorithm;
	board.user_color_pawn=BlackPawn;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
	board.set_pawn_on_field(cord_X,cord_Y,BlackPawn);
	EXPECT_NE(board.change_pawn_on_field(cord_X, cord_Y, WhitePawn), BlackPawn);
}
