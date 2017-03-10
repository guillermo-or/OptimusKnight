#ifndef LEVEL_3_H_
#define LEVEL_3_H_

#include <unordered_set>
#include <vector>
#include <functional>

#include "board.h"
#include "knight.h"
#include "search.h"


std::unordered_set<Move> bounded_dynamics(const Move& m, const Board& b) {
	std::unordered_set<Move> r;
	// filter out moves that take you out of the board.
	for (auto s : dynamics(m)) {
		if (within(b, s)) {
			r.insert(s);
		}
	}
	return r;
}

bool search_shortest(const Move& start, const Move& goal, std::vector<Move>& reverse_path) {
	std::function<std::unordered_set<Move>(Move)> successor = std::bind(
			bounded_dynamics,
			std::placeholders::_1, Board({8,8})
		);
	return bfs<Move>(start, goal, successor, reverse_path);
}

#endif /* LEVEL_3_H_ */
