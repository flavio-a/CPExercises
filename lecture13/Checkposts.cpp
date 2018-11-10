// http://codeforces.com/problemset/problem/427/C?locale=en
/*

A checkpost secures all and only junctions in its strongly connected components:
a junction is secured iff a patrol can go to that junction and come back to the
checkpost iff the checkpost and the junction are in the same SCC.

Thus the problem is to compute the minimum cost of a junction in each SCC, that
is the sum over the SCC of the minimum cost a junction in that SCC. The number
of ways is the product over the SCC of the number of junctions with that minimum
cost.

Time complexity is O(V + E) = O(n + m) to compute the SCC (via DFS). Space
complexity is O(V + E) = O(n + m) to store the graph.

*/

#include <bits/stdc++.h>

using namespace std;

#define lli long long int

void DFS(const vector<vector<unsigned int>> &G, int v, vector<bool> &visited, stack<unsigned int> &f) {
	visited[v] = true;
	for (auto u = G[v].begin(); u != G[v].end(); ++u)
		if (!visited[*u])
			DFS(G, *u, visited, f);
	f.push(v);
}

// During the second DFS each call from the main loop explore exactly a SCC,
// so it's possible to do now any computation needed
void DFS_SCC(const vector<vector<unsigned int>> &G, int v, vector<bool> &visited, const vector<unsigned int> &costs, stack<unsigned int> &mincost, stack<unsigned int> &number) {
	// cout << v << " ";
	visited[v] = true;
	if (costs[v] == mincost.top())
		++number.top();
	if (costs[v] < mincost.top()) {
		mincost.top() = costs[v];
		number.top() = 1;
	}
	for (auto u = G[v].begin(); u != G[v].end(); ++u)
		if (!visited[*u])
			DFS_SCC(G, *u, visited, costs, mincost, number);
}

int main() {
	int N;
	cin >> N;
	vector<unsigned int> costs;
	costs.resize(N);
	for (int i = 0; i < N; ++i)
		cin >> costs[i];
	vector<vector<unsigned int>> G;
	G.resize(N);
	vector<vector<unsigned int>> GT;
	GT.resize(N);
	int M;
	cin >> M;
	for (int i = 0; i < M; ++i) {
		int u, v;
		cin >> u >> v;
		G[u - 1].push_back(v - 1);
		GT[v - 1].push_back(u - 1);
	}

	// cout << "Printing graph:\n";
	// for (int i = 0; i < N + M; ++i) {
	// 	cout << i << ": ";
	// 	for (auto j = G[i].begin(); j != G[i].end(); ++j)
	// 		cout << *j << " ";
	// 	cout << "\n";
	// }

	vector<bool> visited;
	visited.resize(N, false);
	stack<unsigned int> f;

	// Sort by finish time
	for (int i = 0; i < N; ++i)
		if (!visited[i])
			DFS(G, i, visited, f);

	visited.clear();
	visited.resize(N, false);
	stack<unsigned int> mincost;
	stack<unsigned int> number;
	while (!f.empty()) {
		unsigned int v = f.top();
		if (!visited[v]) {
			mincost.push(UINT_MAX);
			number.push(0);
			// cout << v << "'s SSC contains ";
			DFS_SCC(GT, v, visited, costs, mincost, number);
			// cout << "and has mincost = " << mincost.top() << " and number = " << number.top() << "\n";
		}
		f.pop();
	}

	unsigned lli totmincost = 0;
	unsigned lli totnumber = 1;
	while (!mincost.empty()) {
		totmincost += (unsigned lli)mincost.top();
		totnumber = (totnumber * (unsigned lli)number.top()) % 1000000007;

		mincost.pop();
		number.pop();
	}

	cout << totmincost << " " << totnumber << endl;

	return 0;
}
