// https://practice.geeksforgeeks.org/problems/bipartite-graph/1
// TODO
/*



*/

#include <bits/stdc++.h>

using namespace std;

bool isBipartite(const vector<vector<int>> &G, int v, bool color, vector<bool> &visited, vector<bool> &colors) {
	if (visited[v]) {
		if (colors[v] == color)
			return true;
		else
			return false;
	}
	visited[v] = true;
	colors[v] = color;
	for (int u = 0; u < G.size(); ++u)
		if (G[v][u] == 1) {
			if (!isBipartite(G, u, !color, visited, colors))
				return false;
		}
	return true;
}

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;
		vector<vector<int>> G;
		G.resize(N);
		for (int i = 0; i < N; ++i) {
			G[i].resize(N);
			for (int j = 0; j < N; ++j)
				cin >> G[i][j];
		}
		vector<bool> visited, colors;
		visited.resize(N, false);
		colors.resize(N, false);
		cout << (isBipartite(G, 0, true, visited, colors) ? 1 : 0) << "\n";
	}
	return 0;
}
