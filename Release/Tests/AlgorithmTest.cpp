#include <gtest/gtest.h>
#include "../../src/lib/Plansza.h"
#include "../../src/lib/Algorithm.h"
#include "../../src/lib/Display.h"
#include "valueTest.h"


TEST(AlgorithmTest, searchEmptyFields)
{
	Algorithm algorithm;
	Board board;
	board.clear_board();
	EXPECT_EQ(algorithm.search_empty_fields(board), NumberOfEmptyFields);
}

TEST(AlgorithmTest, searchAllowedFields)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	EXPECT_EQ(algorithm.search_allowed_fields(board), NumberOfAllowedField);
}

TEST(AlgorithmTest, checkGoodFieldOnNorth)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	EXPECT_EQ(algorithm.check_field(board, cord_X, cord_Y, 0, 1), PossibleMove);
}

TEST(AlgorithmTest, checkBadFieldOnSouth)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	EXPECT_NE(algorithm.check_field(board, cord_X, cord_Y, 0, -1), PossibleMove);
}

TEST(AlgorithmTest, makeGoodBeat)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	board.set_main_pawns();
	algorithm.clear_cords_empty_field(board);
	algorithm.clear_cords_possible_move(board);
	algorithm.clear_part_pawn_to_beat(board);
	algorithm.clear_cords_check_pawns(board);
	algorithm.search_empty_fields(board);
	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
	EXPECT_EQ(algorithm.make_beat(board,cord_X, cord_Y), 5);
}

TEST(AlgorithmTest, makeBadBeat)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	board.set_main_pawns();
	algorithm.clear_cords_empty_field(board);
	algorithm.clear_cords_possible_move(board);
	algorithm.clear_part_pawn_to_beat(board);
	algorithm.clear_cords_check_pawns(board);
	algorithm.search_empty_fields(board);
	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
	EXPECT_NE(algorithm.make_beat(board,cord_X+1, cord_Y), 5);
}

TEST(AlgorithmTest, makeGoodStats)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	board.set_main_pawns();
	EXPECT_EQ(algorithm.make_stats(board), 2);
}

TEST(AlgorithmTest, makeBadStats)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	EXPECT_NE(algorithm.make_stats(board), 2);
}

TEST(AlgorithmTest, makeGoodStatsAfterBeat)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
	algorithm.make_beat(board,cord_X, cord_Y);
	EXPECT_EQ(algorithm.make_stats(board), 4);
}

TEST(AlgorithmTest, makeBadStatsAfterBeat)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
	algorithm.make_beat(board,cord_X, cord_Y);
	EXPECT_NE(algorithm.make_stats(board), 3);
}

TEST(AlgorithmTest, makeBestMoveCorrect)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	algorithm.clear_cords_empty_field(board);
	algorithm.clear_cords_possible_move(board);
	algorithm.clear_part_pawn_to_beat(board);
	algorithm.clear_cords_check_pawns(board);
	algorithm.search_empty_fields(board);
	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
	algorithm.search_best_move(board);
	EXPECT_EQ(algorithm.make_best_move(board), 0);
}


TEST(AlgorithmTest, searchBestMoveCorrect)
{
	Board board;
	Algorithm algorithm;
	board.clear_board();
	board.set_main_pawns();
	algorithm.search_empty_fields(board);
	algorithm.clear_cords_empty_field(board);
	algorithm.clear_cords_possible_move(board);
	algorithm.clear_part_pawn_to_beat(board);
	algorithm.clear_cords_check_pawns(board);
	algorithm.search_empty_fields(board);
	board.numberOfAllowedMoves=algorithm.search_allowed_fields(board);
	EXPECT_EQ(algorithm.search_best_move(board), 0);
}

