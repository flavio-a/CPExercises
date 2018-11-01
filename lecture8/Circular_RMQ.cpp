// http://codeforces.com/problemset/problem/52/C
/*

Plain implementation of segment tree with lazy updates. Queries that wrap are
handled as two different queries.

*/

#include <bits/stdc++.h>

using namespace std;

typedef struct {
	int min;
	int update;
} minupdate;

int updateSgtree(vector<minupdate> &sgtree, int root, int l, int r, int start, int end, int val) {
	// self lazy update
	if (sgtree[root].update != 0) {
		// cout << "Lazy update of [" << l << "; " << r << "): " << sgtree[root].update << " changes " << sgtree[root].min <<"\n";
		if (l < r - 1) {
			// non-leaf
			sgtree[2 * root].update += sgtree[root].update;
			sgtree[2 * root + 1].update += sgtree[root].update;
		}
		sgtree[root].min += sgtree[root].update;
		sgtree[root].update = 0;
	}
	if (start <= l && r <= end) {
		// Contained
		// cout << "Change [" << l << "; " << r << "): " << val <<"\n";
		if (l < r - 1) {
			// non-leaf
			sgtree[2 * root].update += val;
			sgtree[2 * root + 1].update += val;
		}
		return sgtree[root].min += val;
	}
	else if (end <= l || r <= start) {
		// disjoint
		// cout << "Returning [" << l << "; " << r << "): " << sgtree[root].min <<"\n";
		return sgtree[root].min;
	}
	else {
		// intersect
		if (l < r - 1) {
			int mid = (l + r) / 2;
			int leftmin = updateSgtree(sgtree, 2 * root, l, mid, start, end, val);
			int rightmin = updateSgtree(sgtree, 2 * root + 1, mid, r, start, end, val);
			// cout << "Update from bottom at [" << l << "; " << r << "): " << min(leftmin, rightmin) <<"\n";
			return sgtree[root].min = min(leftmin, rightmin);
		}
		else {
			// leaf
			// cout << "Change [" << l << "; " << r << "): " << val <<"\n";
			return sgtree[root].min += val;
		}
	}
}

int querySgtree(vector<minupdate> &sgtree, int root, int l, int r, int start, int end) {
	// self lazy update
	if (sgtree[root].update != 0) {
		if (l < r - 1) {
			// non-leaf
			sgtree[2 * root].update += sgtree[root].update;
			sgtree[2 * root + 1].update += sgtree[root].update;
		}
		sgtree[root].min += sgtree[root].update;
		sgtree[root].update = 0;
	}
	if (start <= l && r <= end) {
		// node contained in [start; end)
		return sgtree[root].min;
	}
	else if (r <= start || l >= end) {
		// node disjoint from [start; end)
		return INT_MAX;
	}
	else if (l < r - 1) {
		// nonleaf
		int mid = (l + r) / 2;
		int leftmin = querySgtree(sgtree, 2 * root, l, mid, start, end);
		int rightmin = querySgtree(sgtree, 2 * root + 1, mid, r, start, end);
		return min(leftmin, rightmin);
	}
	else {
		// leaf
		return sgtree[root].min;
	}
}

int main() {
	int N;
	cin >> N;
	int A[N];
	vector<minupdate> seg_tree;
	// I'm pretty sure there's a better size limit for the segment tree, but
	// this is working. Maybe I'll fix later
	// IMPROVE
	seg_tree.resize(8 * N, (minupdate){0, 0});
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
		updateSgtree(seg_tree, 1, 0, N, i, i + 1, A[i]);
	}
	// for (int i = 1; i < 2 * N; ++i)
		// cout << i << ": " << seg_tree[i].min << " " << seg_tree[i].update << "\n";

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
			if (lf >= rg) {
				// Wrap
				updateSgtree(seg_tree, 1, 0, N, lf, N, v);
				// for (int i = 1; i < 2 * N; ++i)
				// 	cout << i << ": " << seg_tree[i].min << " " << seg_tree[i].update << "\n";
				updateSgtree(seg_tree, 1, 0, N, 0, rg, v);
				// for (int i = 1; i < 2 * N; ++i)
				// 	cout << i << ": " << seg_tree[i].min << " " << seg_tree[i].update << "\n";
			}
			else {
				updateSgtree(seg_tree, 1, 0, N, lf, rg, v);
				// for (int i = 1; i < 2 * N; ++i)
				// 	cout << i << ": " << seg_tree[i].min << " " << seg_tree[i].update << "\n";
			}
		}
	}

	return 0;
}
