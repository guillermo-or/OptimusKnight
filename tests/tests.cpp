#include "../knight.h"
#include "../board.h"
#include <sstream>

#include "gtest/gtest.h"

TEST(MoveTest, RowsCols)
{
	Move m = {20, 30};
	EXPECT_EQ(20, m.row);
	EXPECT_EQ(30, m.col);
}

TEST(MoveTest, Repr)
{
	std::stringstream fake_cout;
	Move m = {20, 30};
	fake_cout << m;
	EXPECT_EQ("Move(20, 30)", fake_cout.str());
}

TEST(MoveTest, Equality)
{
	Move a = {20, 30};
	Move b = {20, 30};
	Move c = {21, 30};
	Move d = {20, 31};
	EXPECT_TRUE(a == b);
	EXPECT_TRUE(a != c);
	EXPECT_TRUE(a != d);
	EXPECT_TRUE(c != d);
}

TEST(DynamicsTest, NoBoundary)
{
	Move start = {4,4};
	auto successors = dynamics(start);
	std::unordered_set<Move> expected({
		 {5, 6}, {6, 5}, {3, 6}, {6, 3}, {5, 2}, {2, 5}, {3, 2}, {2, 3}
	});
	EXPECT_EQ(expected, successors);
}

TEST(Board, ReprSquare)
{
	Board board = {8,8};
	Move move = {4,4};
	std::string expected =
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . K . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n";
	std::stringstream fake_cout;
	fake_cout << std::tuple<Board, Move>(board, move);
	EXPECT_EQ(expected, fake_cout.str());
}

TEST(Board, ReprRectangle)
{
	Board board = {9,8};
	Move move = {4,5};
	std::string expected =
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . K . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n";
	std::stringstream fake_cout;
	fake_cout << std::tuple<Board, Move>(board, move);
	EXPECT_EQ(expected, fake_cout.str());
}

TEST(Board, ReprRectangleOut)
{
	Board board = {9,8};
	Move move = {40,5};
	std::string expected =
			"There is a Move beyond the board extent!\n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n"
			". . . . . . . . \n";
	std::stringstream fake_cout;
	fake_cout << std::tuple<Board, Move>(board, move);
	EXPECT_EQ(expected, fake_cout.str());
}

TEST(Board, WithinRectangle)
{
	Board board = {9,8};
	Move move = {4,5};
	Move move_boundary = {0,5};
	Move move_wacko1 = {9,8};
	Move move_wacko2 = {9,0};
	EXPECT_TRUE(within(board, move));
	EXPECT_TRUE(within(board, move_boundary));
	EXPECT_FALSE(within(board, move_wacko1));
	EXPECT_FALSE(within(board, move_wacko2));
}
