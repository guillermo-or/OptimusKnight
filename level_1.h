#ifndef LEVEL_1_H_
#define LEVEL_1_H_

#include "knight.h"
#include "board.h"
#include <tuple>

bool is_valid_sequence(std::vector<Move> moves, Board board, std::ostream *os) {

	/*
	Level 1:
		Write a function that accepts a sequence of moves and reports
		whether the sequence contains only valid knight moves. It should also
		optionally print the state of the knight board to the terminal as shown
		above after each move. The current position should be marked with a 'K'.

	Applicant Comments:
		I am taking "reports" to mean "returns".
		I will generalize the option to print the progress to any passed in stream,
			 e.g. `std::cout`.
		I will assume that if the caller passes in a stream, they want all of the
			moves displayed, regardless of legality.
			Indicate if a move is illegal.
			Explicit message if a move goes beyond the extent of the board.
	 */

	std::string board_separator = "\n";
	bool ret = true;

	for (auto move = moves.begin(); move != moves.end(); ++move) {
		if (move != moves.begin()) {
			// There is a more efficient way to check consistency in the trajectories,
			// but this way can use the same function as necessary for search.
			bool dynamics_valid = (dynamics(*(move-1)).count(*move) != 0);
			bool boundary_valid = within(board, *move);
			if (!dynamics_valid || !boundary_valid) {
				ret = false;
				if (os == NULL) {
					// If not printing, can return early.
					break;
				}
				else {
					*os << "The following move is illegal: " << std::endl;
				}
			}
		}

		if (os != NULL) {
			*os << std::tuple<Board, Move>(board, *move);
			*os << board_separator;
		}
	}

	return ret;
}

// https://google.github.io/styleguide/cppguide.html#Default_Arguments
bool is_valid_sequence(std::vector<Move> moves, std::ostream *os) {
	return is_valid_sequence(moves, Board({8,8}), os);
}

bool is_valid_sequence(std::vector<Move> moves) {
	return is_valid_sequence(moves, Board({8,8}), NULL);
}

bool is_valid_sequence(std::vector<Move> moves, Board board) {
	return is_valid_sequence(moves, board, NULL);
}
#endif /* LEVEL_1_H_ */
