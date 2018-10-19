// http://codeforces.com/problemset/problem/52/C
// TODO
/*

Plain implementation of segment tree. Queries that wrap are handled as two
different queries.

*/

#include <bits/stdc++.h>

using namespace std;

int updateSgtree(vector<int> &sgtree, int root, int l, int r, int start, int end, int val) {
	if (l < end && start < r) {
		// intersect
		if (l < r - 1) {
			int mid = (l + r) / 2;
			int leftmin = updateSgtree(sgtree, 2 * root, l, mid, start, end, val);
			int rightmin = updateSgtree(sgtree, 2 * root + 1, mid, r, start, end, val);
			// cout << "Update from bottom at " << root << ": " << min(leftmin, rightmin) <<"\n";
			return sgtree[root] = min(leftmin, rightmin);
		}
		else {
			// cout << "Change at index " << root << ", that is " << l << ": " << val <<"\n";
			return sgtree[root] += val;
		}
	}
	else
		return sgtree[root];
}

int querySgtree(const vector<int> &sgtree, int root, int l, int r, int start, int end) {
	if (start <= l && r <= end) {
		// node contained in [start; end)
		// cout << l << "; " << r << " contained in " << start << "; " << end << "\n";
		return sgtree[root];
	}
	else if (r <= start || l >= end) {
		// node disjoint from [start; end)
		// cout << l << "; " << r << " disjoint from " << start << "; " << end << "\n";
		return INT_MAX;
	}
	else if (l < r - 1) {
		// cout << l << "; " << r << " intersect with " << start << "; " << end << "\n";
		int mid = (l + r) / 2;
		int leftmin = querySgtree(sgtree, 2 * root, l, mid, start, end);
		int rightmin = querySgtree(sgtree, 2 * root + 1, mid, r, start, end);
		return min(leftmin, rightmin);
	}
	else {
		return sgtree[root];
	}
}

int main() {
	int N;
	cin >> N;
	int A[N];
	vector<int> seg_tree;
	seg_tree.resize(2 * N + 1, 0);
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
		updateSgtree(seg_tree, 1, 0, N, i, i + 1, A[i]);
	}
	// updateSgtree(seg_tree, 1, 0, N, 2, 100);
	// for (int i = 1; i < 2 * N + 1; ++i) {
	// 	cout << i << ": " << seg_tree[i] << "\n";
	// }

	// cout << querySgtree(seg_tree, 1, 0, N, 1, 2) << endl;
	// cout << querySgtree(seg_tree, 1, 0, N, 0, 1) << endl;
	// cout << querySgtree(seg_tree, 1, 0, N, 1, 4) << endl;
	// cout << querySgtree(seg_tree, 1, 0, N, 3, 4) << endl;

	int m;
	cin >> m;
	{
		string line;
		getline(cin, line);
	}
	for (int i = 0; i < m; ++i) {
		int lf, rg, v;
		string line;
		getline(cin, line);
		lf = stoi(line.substr(0, line.find(' ')));
		line.erase(0, line.find(' ') + 1);
		if (line.find(' ') == string::npos) {
			rg = stoi(line) + 1;
			// cout << lf << " " << rg << endl;
			// Query
			if (lf >= rg) {
				// Wrap
				cout << min(querySgtree(seg_tree, 1, 0, N, lf, N), querySgtree(seg_tree, 1, 0, N, 0, rg)) << "\n";
			}
			else {
				cout << querySgtree(seg_tree, 1, 0, N, lf, rg) << "\n";
			}
		}
		else {
			// Update
			rg = stoi(line.substr(0, line.find(' '))) + 1;
			line.erase(0, line.find(' ') + 1);
			v = stoi(line);
			// cout << lf << " " << rg << " " << v << endl;
			if (lf >= rg) {
				// Wrap
				updateSgtree(seg_tree, 1, 0, N, lf, N, v);
				updateSgtree(seg_tree, 1, 0, N, 0, rg, v);
			}
			else {
				updateSgtree(seg_tree, 1, 0, N, lf, rg, v);
			}
			// for (int i = 1; i < 2 * N + 1; ++i) {
			// 	cout << i << ": " << seg_tree[i] << "\n";
			// }
		}
	}

	return 0;
}
