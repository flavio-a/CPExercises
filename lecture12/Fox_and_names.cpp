// http://codeforces.com/problemset/problem/510/C?locale=en
// TODO
/*

From the list of names compute a graph as follows: each vertex represents a
letter in the alphabet. Letter u should be before v in the order required iff
there's a path from u to v in that graph. To build it, I just need to add an
edge from u to v when two consecutive words have a common prefix (possibly
empty) and then they have respectively letter u and v.

*/

#include <bits/stdc++.h>

using namespace std;

// Maps lowercase letters to [0; 26]
#define num(l) (l - 'a')

int main() {
	int N;
	cin >> N;
	string words[N];
	for (int i = 0; i < N; ++i)
		cin >> words[i];

	// The graph is an adjacency matrix
	bool G[26][26] = {false};

	for (int i = 1; i < N; ++i) {
		int j = 0;
		while (words[i - 1][j] == words[i][j])
			++j;
		if (words[i - 1][j] < words[i][j]) {
			// Add words[i - 1][j] -> words[i][j]
			G[num(words[i - 1][j])][words[i][j]] = true;
		}
		else {
			// Add words[i - 1][j] <- words[i][j]
			G[num(words[i][j])][words[i - 1][j]] = true;
		}
	}

	// Searches for topological sort, checking also for acyclicness
	

	return 0;
}
