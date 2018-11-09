// http://codeforces.com/problemset/problem/277/A?locale=en
/*

Let's represent each person and each language with a node, and connect with an
edge a person and a language iff that person speaks that language.
Two persons can communicate (via interpreters) iff in this graph they are
connected. Thus the minimum number of laguages to be taught are the number of
connected components containing at least one person (there may be connected
components with a single language).

Space complexity is O(n * m + m * n) = O(nm) to store the graph's adjacency
lists. Time complexity is the DFS time, that is Theta(V * E) = O(nm).

*/

#include <bits/stdc++.h>

using namespace std;

void DFS(const vector<vector<int>> &G, int v, vector<bool> &visited) {
	visited[v] = true;
	for (auto u = G[v].begin(); u != G[v].end(); ++u) {
		if (!visited[*u])
			DFS(G, *u, visited);
	}
}

int main() {
	int N, M;
	cin >> N >> M;
	// Adjacency list
	vector<vector<int>> G;
	G.resize(N + M);
	// Reserve for languages
	for (int i = N; i < N + M; ++i) {
		G[i].reserve(N);
	}

	bool zeroLanguages = true;
	for (int i = 0; i < N; ++i) {
		int k;
		cin >> k;
		zeroLanguages &= k == 0;
		// cout << i << " knows " << k << endl;
		G[i].reserve(k);
		for (int j = 0; j < k; ++j) {
			int l;
			cin >> l;
			// cout << "Adding " << i << " to language " << (l - 1) << endl;
			G[i].push_back(N + l - 1);
			G[N + l - 1].push_back(i);
		}
	}

	// cout << "Printing graph:\n";
	// for (int i = 0; i < N + M; ++i) {
	// 	cout << i << ": ";
	// 	for (auto j = G[i].begin(); j != G[i].end(); ++j)
	// 		cout << *j << " ";
	// 	cout << "\n";
	// }

	if (zeroLanguages) {
		cout << N << endl;
		return 0;
	}

	int cc = 0;
	vector<bool> visited;
	visited.resize(N + M, false);
	for (int i; i < N; ++i) {
		if (!visited[i]) {
			// cout << "Starting DFS of " << i << endl;
			DFS(G, i, visited);
			++cc;
		}
		// else
		// 	cout << i << " already visited";
	}

	cout << (cc - 1) << endl;
	return 0;
}
