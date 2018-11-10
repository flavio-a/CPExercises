// https://practice.geeksforgeeks.org/problems/x-total-shapes/0
/*

Plain DFS to count connected components on the graph of the Xs.

Time and space complexity are both O(N * M) for the DFS and to store the graph,
respectively.

*/

#include <bits/stdc++.h>

using namespace std;

void DFS(const vector<vector<int>> &G, int x, vector<bool> &visited) {
	visited[x] = true;
	for (auto u = G[x].begin(); u != G[x].end(); ++u)
		if (!visited[*u])
			DFS(G, *u, visited);
}

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N, M;
		cin >> N >> M;
		vector<vector<int>> G;
		G.resize(N * M);
		vector<int> Xs;
		Xs.reserve(N * M);
		char line[M];
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				char c;
				cin >> c;
				if (c == 'X') {
					Xs.push_back(i * M + j);
					if (j > 0 && line[j - 1] == 'X') {
						G[i * M + j].push_back(i * M + j - 1);
						G[i * M + j - 1].push_back(i * M + j);
					}
					if (i > 0 && line[j] == 'X') {
						G[i * M + j].push_back((i - 1) * M + j);
						G[(i - 1) * M + j].push_back(i * M + j);
					}
				}
				line[j] = c;
			}
		}

		// for (int i = 0; i < N * M; ++i) {
		// 	cout << "(" << (i / M) << ", " << (i % M) << ") -> ";
		// 	for (auto p = G[i].begin(); p != G[i].end(); ++p) {
		// 		cout << "(" << (*p / M) << ", " << (*p % M) << ") ";
		// 	}
		// 	cout << "\n";
		// }

		int cc = 0;
		vector<bool> visited;
		visited.resize(N * M, false);
		for (auto x = Xs.begin(); x != Xs.end(); ++x) {
			if (!visited[*x]) {
				++cc;
				DFS(G, *x, visited);
			}
		}

		cout << cc << endl;
	}
	return 0;
}
