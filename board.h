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

class BoardRepr {
public:
	Board board_;
	BoardRepr(const Board& board, const std::string& init) :
		board_(board), repr_(
						board_.rows,
						std::vector<std::string>(board_.cols, init)) {};

	// I considered overloading [], but I did not want to handle the complexity of
	// a partial index like: `board_repr[3]`
	std::string& get(int row, int col) {
		// out-of-bounds errors passed onto underlying data structure.
		return repr_[row][col];
	}

private:
	// would ideally be a std::dynarray since size should not change after construction.
	// as a compromise, make it private
	std::vector<std::vector<std::string> > repr_;

	// https://google.github.io/styleguide/cppguide.html#Friends
	friend std::ostream& operator<<(std::ostream& os, BoardRepr board_repr);
};

bool within(Board b, Move m) {
	return (0 <= m.row && 0 <= m.col) && (m.row < b.rows && m.col < b.cols);
}

std::ostream& operator<<(std::ostream& os, BoardRepr board_repr) {
	std::vector<std::vector<std::string> > repr = board_repr.repr_;
	for (auto row = repr.begin(); row != repr.end(); ++row) {
		for (auto el = row->begin(); el != row->end(); ++el) {
			os << *el << " "; // will produce a trailing space
		}
		os << std::endl; // will produce a trailing newline.
	}
	return os;
}

// Print a board and one move.
std::ostream& operator<<(std::ostream& os, const std::tuple<Board, Move>& print) {
	Board board = std::get<0>(print);
	Move move = std::get<1>(print);

	std::string empty = ".";
	std::string knight = "K";

	BoardRepr board_repr(board, empty);

	if (within(board, move)) {
		board_repr.get(move.row, move.col) = knight;
	}
	else {
		os << "There is a Move beyond the board extent!" << std::endl;
	}

	os << board_repr;
	return os;
}

#endif /* BOARD_H_ */
