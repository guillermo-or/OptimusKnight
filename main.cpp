#include "level_3.h"
#include <iostream>

int main(void)
{
	// https://google.github.io/styleguide/cppguide.html#Braced_Initializer_List
	Board board = {8, 8};
	BoardRepr board_repr(Board({8,8}), "");

	int max_so_far = 0;

	// For board with (2^3)^2 positions, there are ((2^3)^2)^2 = 2^12 iterations
	for (int r = 0; r < board.rows; ++r) {
		for (int c = 0; c < board.cols; ++c) {
			for (int rr = 0; rr < board.cols; ++rr) {
				for (int cc = 0; cc < board.cols; ++cc) {
					auto start = Move({r,c});
					auto goal = Move({rr,cc});
					std::vector<Move> path;
					search_shortest(start, goal, path);
					int path_length = path.size();	// not exactly path length for start == goal
					if (path_length > max_so_far) {
						std::cout << "found longer: " << path_length <<
								" from " << start << " to " << goal << std::endl;
						max_so_far = path_length;
					}
				}
			}
		}
	}
	return 0;
}
