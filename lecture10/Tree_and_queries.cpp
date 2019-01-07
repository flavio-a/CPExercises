// http://codeforces.com/contest/375/problem/D
/*

First I linearize the tree with a preorder visit, so that subtrees goes into
subarrays. This way a query on a subtree becomes a query on a subarray, and I
can use Mo's algorithm.

Space complexity is Theta(N + M + maxC) where maxC is the maximum number of
possible colors for many support arrays. Time complexity is O((N + M) * sqrt(N))
because it's Mo's algorithm with constant add and remove.

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
	ios_base::sync_with_stdio(false);

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

	vector<int> v(M), k(M), qidx(M);
	for (int j = 0; j < M; ++j) {
		cin >> v[j] >> k[j];
		--v[j];
		qidx[j] = j;
	}
	const int sqrtN = sqrt(N);
	sort(qidx.begin(), qidx.end(), [&start, &end, &v, &sqrtN](int a, int b) {
		if (start[v[a]] / sqrtN != start[v[b]] / sqrtN) {
			return start[v[a]] / sqrtN < start[v[b]] / sqrtN;
		}
		return end[v[a]] < end[v[b]];
	});

	vector<int> totfreq(maxC, 0), col2freq(maxC, 0);
	auto add = [&totfreq, &col2freq](int c){
		++col2freq[c];
		++totfreq[col2freq[c]];
	};
	auto rem = [&totfreq, &col2freq](int c){
		--totfreq[col2freq[c]];
		--col2freq[c];
	};
	vector<int> results(M);
	int s = 0, e = 0;
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
		results[sIdx] = totfreq[k[sIdx]];
	}

	for (int j = 0; j < M; ++j) {
		cout << results[j] << "\n";
	}

	return 0;
}
