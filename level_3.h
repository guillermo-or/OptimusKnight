#ifndef LEVEL_3_H_
#define LEVEL_3_H_

#include <unordered_set>
#include <vector>
#include "board.h"
#include "knight.h"
#include "search.h"


std::unordered_set<Move> bounded_dynamics(Move m) {
	std::unordered_set<Move> r;
	// filter out moves that take you out of the board.
	for (auto s : dynamics(m)) {
		if (within(Board({8,8}), s)) {
			r.insert(s);
		}
	}
	return r;
}

bool search_shortest(const Move& start, const Move& goal, std::vector<Move>& reverse_path) {
	return bfs<Move>(start, goal, bounded_dynamics, reverse_path);
}

#endif /* LEVEL_3_H_ */
