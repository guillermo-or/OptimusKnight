#ifndef BOARD_H_
#define BOARD_H_

#include <tuple>
#include <vector>
#include <unordered_set>
#include <string>
#include "knight.h"

struct Board {
	int rows;
	int cols;
};

bool within(Board b, Move m) {
	return (0 <= m.row && 0 <= m.col) && (m.row < b.rows && m.col < b.cols);
}

void print_string_grid(std::ostream& os, std::vector<std::vector<std::string> > repr) {
	for (auto row = repr.begin(); row != repr.end(); ++row) {
		for (auto el = row->begin(); el != row->end(); ++el) {
			os << *el << " "; // will produce a trailing space
		}
		os << std::endl; // will produce a trailing newline.
	}
}

// Print a board and one move.
std::ostream& operator<<(std::ostream& os, const std::tuple<Board, Move>& print) {
	Board board = std::get<0>(print);
	Move move = std::get<1>(print);

	std::string empty = ".";
	std::string knight = "K";

	std::vector<std::vector<std::string> > repr(
							board.rows,
							std::vector<std::string>(board.cols, empty));

	if (within(board, move)) {
		repr[move.row][move.col] = knight;
	}
	else {
		os << "There is a Move beyond the board extent!";
	}

	print_string_grid(os, repr);
	return os;
}

#endif /* BOARD_H_ */
