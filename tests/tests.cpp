#include "../knight.h"
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
