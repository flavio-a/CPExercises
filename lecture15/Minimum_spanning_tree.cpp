// https://www.spoj.com/problems/MST/
/*

Kruskal.

*/

#include <bits/stdc++.h>

using namespace std;

typedef struct _triple {
	int u, v, w;
} triple;

void unite(int x, int y, vector<int> &parent, vector<int> &rank) {
	if (rank[x] < rank[y])
		parent[x] = y;
	else
		parent[y] = x;
	if (rank[x] == rank[y])
		++rank[y];
}

int main() {
	int N, M;
	cin >> N >> M;
	triple E[M];
	for (int i = 0; i < M; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		E[i].u = u - 1;
		E[i].v = v - 1;
		E[i].w = w;
	}
	sort(E, E + M, [&](triple a, triple b) { return a.w < b.w; });
	vector<int> parent(N);
	iota(parent.begin(), parent.end(), 0);
	vector<int> rank(N, 0);

	function<int(int)> find = [&](int x) {
		if (parent[x] == x)
			return x;
		return parent[x] = find(parent[x]);
	};
	auto unite = [&](int x, int y) {
		x = find(x);
		y = find(y);
		if (rank[x] < rank[y])
			parent[x] = y;
		else
			parent[y] = x;
		if (rank[x] == rank[y])
			++rank[y];
	};

	unsigned long long int sum = 0;
	for (auto e: E) {
		if (find(e.u) != find(e.v)) {
			unite(e.u, e.v);
			sum += (unsigned long long int)e.w;
		}
	}

	cout << sum << endl;

	return 0;
}
