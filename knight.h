#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>

struct Move {
	// against https://google.github.io/styleguide/cppguide.html#Access_Control
	int row;
	int col;
};

std::ostream& operator<<(std::ostream& os, const Move& move) {
	os << "Move(" << move.row << ", "<< move.col << ")";
	return os;
}

struct Board {
	int rows;
	int cols;
};
#endif
