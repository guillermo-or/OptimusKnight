#ifndef LEVEL_2_H_
#define LEVEL_2_H_

#include "board.h"
#include "knight.h"

std::vector<Move> slide_col_skill_base = {{0, 0}, {1, 2}, {2, 0}, {0, 1}};

std::vector<Move> flip_row (const std::vector<Move>& in) {
	std::vector<Move> out;
	for (auto in_move : in) {
		out.push_back(Move({-in_move.row, in_move.col}));
	}
	return out;
}

std::vector<Move> rotate (const std::vector<Move>& in) {
	std::vector<Move> out;
	for (auto in_move : in) {
		out.push_back(Move({in_move.col, -in_move.row}));
	}
	return out;
}

std::vector<Move> reverse (const std::vector<Move>& in) {
	std::vector<Move> out(in.rbegin(), in.rend()); // reverse copy
	return out;
}

std::vector<Move> slide_col (const std::vector<Move>& in) {
	std::vector<Move> out;
	for (auto in_move : in) {
		out.push_back(Move({in_move.row, in_move.col-1}));
	}
	return out;
}

std::vector<Move> translate (const std::vector<Move>& in, const Move& start) {
	std::vector<Move> out;
	for (auto in_move : in) {
		out.push_back(Move({in_move.row + start.row, in_move.col + start.col}));
	}
	return out;
}

// There are a few symmetries in the "skill", and we need to exploit it so that
// the skill is applicable in all of the edges and corners.
// In a group-theoretic perspective, concatenating two paths is a group operation,
// And `slide_col_skills` is a generating set for the set of all (start, goal) end points.

std::vector<std::vector<Move> > slide_col_skills = {
		slide_col_skill_base,
		flip_row(slide_col_skill_base),
		rotate(rotate(slide_col(reverse(slide_col_skill_base)))),
		flip_row(rotate(rotate(slide_col(reverse(slide_col_skill_base)))))
};

void chain_skills(const Move& start, const Move& goal, std::vector<Move>& path, Board board) {
	// We have skills for incrementing one dimension (row or column) in any edge/corner situation.
	// So first displace all the rows you need, and then all the columns.
	// `path` contains `start` and `goal`, unless start==goal,
	// in which case it only contains one copy.
	// If start or goal are infeasible, return an incomplete path.
	path.push_back(start);

	// move in the col direction
	int col_move = goal.col - start.col;
	for (int step = 0; step < std::abs(col_move); ++step) {
		for (auto skill : slide_col_skills) {
			if (col_move < 0) {
				skill = rotate(rotate(skill));
			}
			auto new_segment = translate(skill, path.back());
			// The skill is already "dynamically feasible", so really only need
			// to check boundaries, but check anyway.
			if (is_valid_sequence(new_segment, board)) {
				// append this path.
				path.insert(std::end(path), std::begin(new_segment)+1, std::end(new_segment));
				break; // Don't need to keep trying skills
			}
		}
	}

	// now do the same thing in the row direction
	// code repetition might improve clarity in this case...
	int row_move = goal.row - start.row;
	for (int step = 0; step < std::abs(row_move); ++step) {
		for (auto skill : slide_col_skills) {
			skill = rotate(skill); // now increases row by 1.
			if (row_move < 0) {
				skill = rotate(rotate(skill));
			}
			auto new_segment = translate(skill, path.back());
			// The skill is already "dynamically feasible", so really only need
			// to check boundaries, but check anyway.
			if (is_valid_sequence(new_segment, board)) {
				// append this path.
				path.insert(std::end(path), std::begin(new_segment)+1, std::end(new_segment));
				break; // Don't need to keep trying skills
			}
		}
	}
}

#endif /* LEVEL_2_H_ */
