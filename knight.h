#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>

struct Move {
	// against https://google.github.io/styleguide/cppguide.html#Access_Control
	int row;
	int col;
};

// naive hash of `Move`. Consider not putting this in std, but instead template containers with
// this hash function.
namespace std {
	template <> struct hash<Move> {
		size_t operator()(const Move& m) const {
			return hash<int>()(m.row) ^ hash<int>()(m.col);
		}
	};
}

// I did not find an opinion on the Google style guide regarding member vs not member
// operator overloading.
// Here's one: http://stackoverflow.com/a/4421729/415404
bool operator==(const Move& lhs, const Move& rhs ) {
	return std::tie(lhs.row, lhs.col) == std::tie(rhs.row, rhs.col);
	//return (lhs.row==rhs.row) && (lhs.col==rhs.col);
}

bool operator!=(const Move& lhs, const Move& rhs){ return !operator==(lhs,rhs); }


std::ostream& operator<<(std::ostream& os, const Move& move) {
	os << "Move(" << move.row << ", "<< move.col << ")";
	return os;
}


std::unordered_set <Move> dynamics(const Move& now) {
	std::unordered_set <Move> neighbors;
	std::vector< int > twos = {-2, 2};
	std::vector< int > ones = {-1, 1};

	// https://google.github.io/styleguide/cppguide.html#auto
	for (auto two = twos.begin(); two != twos.end(); ++two) {
		for (auto one = ones.begin(); one != ones.end(); ++one) {
			Move m_rc = {now.row + *two, now.col + *one};
			Move m_cr = {now.row + *one, now.col + *two};
			neighbors.insert(m_rc);
			neighbors.insert(m_cr);
		}
	}
	return neighbors;
}

#endif /* KNIGHT_H_ */
