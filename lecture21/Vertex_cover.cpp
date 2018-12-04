// https://practice.geeksforgeeks.org/problems/missing-number-in-array/0
/*

Vertex cover is the dual problem of largest independent set, thus its solution
is N (number of nodes) minus the size of the largest independent set. This is
computed as seen at class.

*/

#include <bits/stdc++.h>

using namespace std;

// Computes largest independent set on trees using DFS, and in the meantime
// roots the tree in root. Actually returns the LIST of root and the sum of the
// LISTs of root's children.
pair<int, int> LIST(vector<vector<int>> &G, int root) {
	int sonssum = 0;
	int grandsonssum = 0;
	for (auto v : G[root]) {
		// Removes root from v's sons. The sum over all the lists has a total
		// cost of Theta(E), already in the DFS
		G[v].erase(find(G[v].begin(), G[v].end(), root));
		auto p = LIST(G, v);
		sonssum += p.first;
		grandsonssum += p.second;
	}
	return pair<int, int>(max(1 + grandsonssum, sonssum), sonssum);
}

int main() {
	int N;
	cin >> N;
	// Graph representation
	vector<vector<int>> G;
	G.resize(N);
	for (int i = 1; i < N; ++i) {
		int u, v;
		cin >> u >> v;
		G[u - 1].push_back(v - 1);
		G[v - 1].push_back(u - 1);
	}
	cout << (N - LIST(G, 0).first) << endl;
	return 0;
}
