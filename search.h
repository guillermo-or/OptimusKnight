#ifndef SEARCH_H_
#define SEARCH_H_

#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>
#include <functional>

template <typename PathElement>
bool bfs(const PathElement& start, const PathElement& goal,
		std::function<std::unordered_set<PathElement>(PathElement)> successor,
		std::vector<PathElement>& reverse_path) {
	// returned path does not include `start`.
	// but it always includes `goal`.
	// That means that reverse_path.size()=1 means that either 0 or 1 moves were required.
	// (Other possible design choice is to return an empty path if start == goal)

	// These are nodes to which we know the shortest path.
	std::unordered_map<PathElement, PathElement> parents;
	parents[start] = start; // sentinal value

	//Search frontier.
	std::queue<PathElement> agenda;
	agenda.push(start);

	// Note an invariant:
	// whenever something is pushed to `agenda`, it must be in `parents`.

	while (!agenda.empty()) {
		PathElement parent = agenda.front(); agenda.pop();
		std::unordered_set<PathElement> successors = successor(parent);

		for (auto child = successors.begin(); child != successors.end(); ++child) {
			// It could be more elegant to implement this as a set operation
			// (next - parents), but built-in implementations appear to be linear
			// in the size of both sets, and require elements to be orderable.
			if (parents.count(*child) > 0) { continue; }	// already know shortest path
			parents[*child] = parent;
			agenda.push(*child);
		}
	}	// could terminate early if goal is popped.

	if (parents.count(goal)==0) { return false; }	// no path

	PathElement e = goal;
	while (true) {
		reverse_path.push_back(e);
		e = parents[e];
		// Need to check at the end so that we return a path even if start == goal;
		if (e == start) { break; }
	}
	return true;
}


#endif /* SEARCH_H_ */
