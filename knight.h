#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>

struct Move
{
	int row;
	int col;
};

std::ostream& operator<<(std::ostream& os, const Move& move)
{
	os << "Move(" << move.row << ", "<< move.col << ")";
	return os;
}

struct Board
{
	int rows;
	int cols;
};
#endif
