// http://codeforces.com/contest/375/problem/D
// TODO
/*

Easy (with respect to the N * log N one) solution with Mo's algorithm.

*/

#include <bits/stdc++.h>

using namespace std;

#define maxC 100001

int linearize(vector<vector<int>> &G, int root, int parent, const vector<int> &colors, int idx, vector<int> &start, vector<int> &end, vector<int> &newcolors) {
	start[root] = idx;
	newcolors[idx] = colors[root];
	++idx;
	for (int v : G[root]) {
		if (v != parent) {
			idx = linearize(G, v, root, colors, idx, start, end, newcolors);
		}
	}
	end[root] = idx;
	return idx;
}

int main() {
	int N, M;
	cin >> N >> M;
	vector<int> colors(N);
	for (int i = 0; i < N; ++i) {
		cin >> colors[i];
	}

	vector<vector<int>> G(N);
	for (int i = 0; i < N - 1; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	vector<int> start(N), end(N), newcolors(N);
	linearize(G, 0, -1, colors, 0, start, end, newcolors);

	// for (int i = 0; i < N; ++i) {
	// 	cout << "Node " << i << ": [" << start[i] << "; " << end[i] << "), color " << newcolors[i] << "\n";
	// }

	vector<int> v(M), k(M), qidx(M);
	for (int j = 0; j < M; ++j) {
		cin >> v[j] >> k[j];
		--v[j];
		qidx[j] = j;
	}
	const int sqrtN = floor(sqrt(N));
	sort(qidx.begin(), qidx.end(), [&](int a, int b) {
		if (start[a] / sqrtN != start[b] / sqrtN) {
			return start[a] / sqrtN < start[b] / sqrtN;
		}
		return end[a] < end[b];
	});

	vector<int> results(M);
	int s = 0, e = 0;
	vector<int> totfreq(maxC, 0), col2freq(maxC, 0);
	auto add = [&totfreq, &col2freq](int c){
		++col2freq[c];
		++totfreq[col2freq[c]];
	};
	auto rem = [&totfreq, &col2freq](int c){
		--totfreq[col2freq[c]];
		--col2freq[c];
	};
	for (int j = 0; j < M; ++j) {
		// query qidx[j]
		int sIdx = qidx[j];
		while (s < start[v[sIdx]]) {
			rem(newcolors[s]);
			++s;
		}
		while (s > start[v[sIdx]]) {
			--s;
			add(newcolors[s]);
		}
		while (e < end[v[sIdx]]) {
			add(newcolors[e]);
			++e;
		}
		while (e > end[v[sIdx]]) {
			--e;
			rem(newcolors[e]);
		}
		// cout << "Query " << sIdx << ": [" << s << "; " << e << ")\n";
		// for (int i = 1; i < 4; ++i) {
		// 	cout << "col2freq[" << i << "] = " << col2freq[i] << "\n";
		// }
		results[sIdx] = totfreq[k[sIdx]];
	}

	for (int j = 0; j < M; ++j) {
		cout << results[j] << "\n";
	}

	return 0;
}
