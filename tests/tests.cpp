#include "../knight.h"
#include "../board.h"
#include "../level_1.h"
#include "../level_3.h"
#include "../level_2.h"
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

TEST(Level1, ValidSequence)
{
	Board board = {8,8};
	std::vector<Move> moves = {{4,4}, {5,6}, {4,4}, {5,2}};
	EXPECT_TRUE(is_valid_sequence(moves));
}

TEST(Level1, InvalidSequenceDynamics)
{
	Board board = {8,8};
	std::vector<Move> moves = {{4,4}, {5,6}, {4,4}, {5,5}};
	EXPECT_FALSE(is_valid_sequence(moves));
}

TEST(Level1, InvalidSequenceBoundary)
{
	Board board = {8,8};
	std::vector<Move> moves = {{4,4}, {5,6}, {6,8}};
	EXPECT_FALSE(is_valid_sequence(moves));
}

TEST(Level1, ValidSequencePrint)
{
	Board board = {8,8};
	std::vector<Move> moves = {{4,4}, {5,6}, {4,4}, {5,2}};
	// not testing output, but printing to stdout.
	EXPECT_TRUE(is_valid_sequence(moves, &std::cout));
}

TEST(Level1, InvalidSequenceDynamicsPrint)
{
	Board board = {8,8};
	std::vector<Move> moves = {{4,4}, {5,6}, {4,4}, {5,5}};
	// not testing output, but printing to stdout.
	EXPECT_FALSE(is_valid_sequence(moves, &std::cout));
}

TEST(Level1, InvalidSequenceBoundaryPrint)
{
	Board board = {8,8};
	std::vector<Move> moves = {{4,4}, {5,6}, {6,8}};
	// not testing output, but printing to stdout.
	EXPECT_FALSE(is_valid_sequence(moves, &std::cout));
}


TEST(Level3, SearchTrivial)
{
	std::vector<Move> path;
	bool found_path = search_shortest(Move({4,4}), Move({4,4}), path);
	EXPECT_TRUE(found_path);
	EXPECT_EQ(std::vector<Move>({{4,4}}), path);
}

TEST(Level3, SearchOneStep)
{
	std::vector<Move> path;
	bool found_path = search_shortest(Move({4,4}), Move({5,6}), path);
	EXPECT_TRUE(found_path);
	EXPECT_EQ(std::vector<Move>({{5,6}}), path);
}

TEST(Level3, SearchInfeasable)
{
	std::vector<Move> path;
	bool found_path = search_shortest(Move({4,4}), Move({10,10}), path);
	EXPECT_FALSE(found_path);
}

TEST(Level3, SearchInteresting)
{
	std::vector<Move> path;
	auto start = Move({0,0});
	bool found_path = search_shortest(start, Move({7,7}), path);
	EXPECT_TRUE(found_path);

	BoardRepr board_repr(Board({8,8}), "");
	// mark the start.
	board_repr.get(start.row, start.col) = "S";
	update(board_repr, path);
	board_repr.fill_empty(".");
	std::cout << board_repr;
	// There may be multiple shortest paths, so just check the length.
	EXPECT_EQ(6, path.size());
}

TEST(Level3, SearchBig)
{
	std::vector<Move> path;
	auto start = Move({0,0});
	Board board = {17, 27};
	std::function<std::unordered_set<Move>(Move)> successor = std::bind(
			bounded_dynamics,
			std::placeholders::_1, board
		);

	bool found_path = bfs(start, Move({16,26}), successor, path);
	EXPECT_TRUE(found_path);

	BoardRepr board_repr(board, "");
	// mark the start.
	board_repr.get(start.row, start.col) = "S";
	update(board_repr, path);
	board_repr.fill_empty(".");
	std::cout << board_repr;
	// There may be multiple shortest paths, so just check the length.
	EXPECT_EQ(14, path.size());
}

TEST(Level2, SkillSetValid)
{
	for (auto skill : slide_col_skills) {
		auto skill_moved = translate(skill, Move({4,4}));
		EXPECT_TRUE(is_valid_sequence(skill_moved));
		BoardRepr board_repr(Board({8,8}), "");
		update(board_repr, skill_moved);
		board_repr.fill_empty(".");
		std::cout << "Skill" << std::endl << board_repr;
	}
}

void chain_skills_test_helper(Move start, Move goal, Board board) {
	std::vector<Move> path;
	chain_skills(start, goal, path, board);
	EXPECT_TRUE(is_valid_sequence(path));
	EXPECT_EQ(goal, path.back());
	EXPECT_EQ(start, path.front());
}
TEST(Level2, Corners)
{
	Board board = {8, 8};
	chain_skills_test_helper(Move({0,0}), Move({0,1}), board);
	chain_skills_test_helper(Move({0,0}), Move({1,0}), board);
	chain_skills_test_helper(Move({0,7}), Move({0,6}), board);
	chain_skills_test_helper(Move({0,7}), Move({1,7}), board);
	chain_skills_test_helper(Move({7,7}), Move({7,6}), board);
	chain_skills_test_helper(Move({7,7}), Move({6,7}), board);
	chain_skills_test_helper(Move({7,0}), Move({7,1}), board);
	chain_skills_test_helper(Move({7,0}), Move({6,0}), board);
}

TEST(Level2, LongMove)
{
	Move start = {0, 0};
	Move goal = {7, 7};
	Board board = {8, 8};
	std::vector<Move> path;
	chain_skills(start, goal, path, board);

	BoardRepr board_repr(board, "");
	update(board_repr, path);
	board_repr.fill_empty(".");
	EXPECT_TRUE(is_valid_sequence(path));
	EXPECT_EQ(goal, path.back());
	EXPECT_EQ(start, path.front());
	std::cout << "Chained Skills" << std::endl << board_repr;
}

TEST(Level2, LongMoveOpposite)
{
	Move start = {7, 7};
	Move goal = {0, 0};
	Board board = {8, 8};
	std::vector<Move> path;
	chain_skills(start, goal, path, board);

	BoardRepr board_repr(board, "");
	update(board_repr, path);
	board_repr.fill_empty(".");
	EXPECT_TRUE(is_valid_sequence(path));
	EXPECT_EQ(goal, path.back());
	EXPECT_EQ(start, path.front());
	std::cout << "Chained Skills" << std::endl << board_repr;
}
