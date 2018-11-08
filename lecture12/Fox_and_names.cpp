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
#define letter(n) (char)(n + 'a')

// Returns false iff it found a cycle
bool recursiveDFS(const bool G[26][26], char v, vector<char> &colors, stack<char> &order) {
	colors[v] = 1;
	// Visit neighbours
	for (int i = 0; i < 26; ++i) {
		if (G[v][i]) {
			// i is a neighbour
			if (colors[i] == 1)
				// v is a descendant of i, cycle
				return false;
			if (colors[i] == 0) {
				if (!recursiveDFS(G, i, colors, order))
					return false;
			}
		}
	}
	colors[v] = 2;
	// cout << "Pushing " << letter(v) << "\n";
	order.push(v);
	return true;
}

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
		while (j < words[i - 1].length() && j < words[i].length() && words[i - 1][j] == words[i][j])
			++j;
		if (j < words[i - 1].length() && j < words[i].length())
			// Add words[i - 1][j] -> words[i][j]
			G[num(words[i - 1][j])][num(words[i][j])] = true;
	}

	stack<char> order;
	vector<char> colors;
	colors.resize(26, 0);

	// Searches for topological sort, checking also for acyclicness
	for (int v = 0; v < 26; ++v) {
		if (colors[v] == 0) {
			if (!recursiveDFS(G, v, colors, order)) {
				cout << "Impossible" << endl;
				return 0;
			}
		}
	}

	while (!order.empty()) {
		cout << letter(order.top());
		order.pop();
	}

	return 0;
}
