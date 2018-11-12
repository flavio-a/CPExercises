// http://codeforces.com/contest/375/problem/D
// TODO
/*

Easy (with respect to the N * log N one) solution with Mo's algorithm.

*/

#include <bits/stdc++.h>

using namespace std;

int linearizer(const vector<vector<int>> &G, const vector<int> &oldcolors, int u, int idx, vector<int> &newcolors, vector<pair<int, int>> &boundaries) {
	boundaries[u] = pair<int, int>(idx, 0);
	newcolors[u] = oldcolors[u];
	++idx;
	for (auto v = G[u].begin(); v != G[u].end(); ++v)
		if (newcolors[*v] != oldcolors[*v])
			idx = linearizer(G, oldcolors, *v, idx, newcolors, boundaries);
	// The subarray corresponding to the subtree is [first; second)
	boundaries[u].second = idx;
	return idx;
}

int main() {
	int N, M;
	cin >> N >> M;
	vector<int> colors;
	colors.reserve(N);
	for (int i = 0; i < N; ++i) {
		int tmp;
		cin >> tmp;
		colors.push_back(tmp - 1);
	}
	vector<vector<int>> G;
	G.resize(N);
	for (int i = 0; i < N - 1; ++i) {
		int u, v;
		cin >> u >> v;
		G[u - 1].push_back(v - 1);
		G[v - 1].push_back(u - 1);
	}

	// Linearize the tree with a preorder visit
	vector<int> newcolors;
	newcolors.resize(N, -1);
	vector<pair<int, int>> boundaries;
	boundaries.resize(N);
	linearizer(G, colors, 0, 0, newcolors, boundaries);
	// for (int i = 0; i < N; ++i)
	// 	cout << "Subtree of " << i << " is [" << boundaries[i].first << ", " << boundaries[i].second << "), color " << newcolors[i] << "\n";

	vector<pair<int, int>> queries;
	for (int i = 0; i < M; ++i) {
		int v, k;
		cin >> v >> k;
		queries.push_back(pair<int, int>(v - 1, k));
	}

	int Qindexes[M];
	iota(Qindexes, Qindexes + M, 0);
	int sqrtN = ceil(sqrt(N));
	// Sort queries by (bucket; end)
	sort(Qindexes, Qindexes + M, [sqrtN, N, &queries, &boundaries](int i1, int i2) {
		auto p1 = boundaries[queries[i1].first], p2 = boundaries[queries[i2].first];
		if (p1.first / sqrtN == p2.first / sqrtN)
			return p1.second < p2.second;
		// Given that the two elements are in distinct buckets, it's enough to
		// compare the values of l
		return p1.first < p2.first;
	});


	#define MAX_COLOR 100001
	int occ[MAX_COLOR] = {0};
	// there are k_occ[i] colors that appears at least i times
	int k_occ[MAX_COLOR] = {0};
	vector<int> results;
	results.resize(M);
	int l = 0, r = 0;
	for (int i = 0; i < M; ++i) {
		// Query Qindexes[i]
		auto borders = boundaries[queries[Qindexes[i]].first];
		cout << "Query " << i << " -> " << Qindexes[i] << endl;
		cout << queries[Qindexes[i]].second << " [" << borders.first << ", " << borders.second << ")\n";
		while (r > borders.second) {
			// cout << "-r " << r << " " << newcolors[r] << endl;
			k_occ[occ[newcolors[r]]]--;
			occ[newcolors[r]]--;
			--r;
		}
		while (r < borders.second) {
			// cout << "+r " << r << " " << newcolors[r] << endl;
			occ[newcolors[r]]++;
			k_occ[occ[newcolors[r]]]++;
			++r;
		}
		while (l < borders.first) {
			// cout << "+l " << l << " " << newcolors[l] << endl;
			k_occ[occ[newcolors[l]]]--;
			occ[newcolors[l]]--;
			++l;
		}
		while (l > borders.first) {
			--l;
			// cout << "-l " << l << " " << newcolors[l] << endl;
			occ[newcolors[l]]++;
			k_occ[occ[newcolors[l]]]++;
		}
		// for (int i = 0; i < 5; ++i)
		// 	cout << "Color " << i << ": " << occ[i] << endl;
		// for (int i = 1; i < 5; ++i)
		// 	cout << "k_occ " << i << ": " << k_occ[i] << endl;
		results[Qindexes[i]] = k_occ[queries[Qindexes[i]].second];
	}

	for (int i = 0; i < M; ++i)
		cout << results[i] << "\n";

	return 0;
}
