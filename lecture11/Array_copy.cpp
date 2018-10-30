// https://practice.geeksforgeeks.org/problems/missing-number-in-array/0
// TODO
/*

The array B is never modified, and update operations are stored in a segment
tree over the array B. Each node of the tree keeps information on the last query
that completely contains it (and a flag to remember that the information is
valid) and the actual informations. Updates are updates on the segment tree,
with the difference that a valid information is propagated to its sons before
the update. Queries are done exploring the segment tree.

Space complexity is Theta(n) for the segment tree. Time complexity is O(m log n)
because each operation (both copy and access) is an operation on the segment
tree.

*/

#include <bits/stdc++.h>

using namespace std;

typedef struct {
	int delta;
	bool valid;
} deltavalid;

const deltavalid empty = {0, false};

// Segment tree
void update(vector<deltavalid> &sgtree, int node, int left, int right, int s, int e, int delta) {
	// cout << "Update " << " [" << left << "; " << right << ")" << " with " << delta << endl;
	if (s <= left && right <= e) {
		// node contained
		// cout << "Change valid " << " [" << left << "; " << right << ")" << " with " << delta << endl;
		sgtree[node].valid = true;
		sgtree[node].delta = delta;
	}
	else if (s >= right || e <= left) {
		// node disjoint
		return;
	}
	else {
		// node intersect
		int mid = (left + right) / 2;
		if (sgtree[node].valid) {
			// prevois delta valid, should propagate
			// update(sgtree, 2 * node, left, mid, left, right, sgtree[node].delta);
			// update(sgtree, 2 * node + 1, mid, right, left, right, sgtree[node].delta);

			// actually those two recursive calls are always node contained, so
			// I replace the code for efficiency
			sgtree[2 * node].valid = true;
			sgtree[2 * node].delta = sgtree[node].delta;
			sgtree[2 * node + 1].valid = true;
			sgtree[2 * node + 1].delta = sgtree[node].delta;
		}
		// now previous delta invalid, neglected
		sgtree[node].valid = false;
		update(sgtree, 2 * node, left, mid, s, e, delta);
		update(sgtree, 2 * node + 1, mid, right, s, e, delta);
	}
}

deltavalid query(const vector<deltavalid> &sgtree, int node, int left, int right, int i) {
	// cout << "Query " << node << " [" << left << "; " << right << ")" << endl;
	if (left <= i && i < right) {
		// i within the node
		if (sgtree[node].valid)
			return sgtree[node];
		if (left + 1 == right)
			return empty;
		int mid = (left + right) / 2;
		deltavalid tmp = query(sgtree, 2 * node, left, mid, i);
		if (tmp.valid)
			return tmp;
		else
			return query(sgtree, 2 * node + 1, mid, right, i);
	}
	else
		return empty;
}

int main() {
	int N, M;
	cin >> N >> M;
	int A[N], B[N];
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	for (int i = 0; i < N; ++i)
		cin >> B[i];

	// Size is 4 * N for the following: 2 * N >= 2^k >= N for the right k.
	// Now an array with 2^k elements has a segment tree with 2 * 2^k - 1
	// elements, that is < 4 * N
	vector<deltavalid> sgtree(4 * N, empty);

	for (int m = 0; m < M; ++m) {
		int kind;
		cin >> kind;
		if (kind == 1) {
			int x, y, k;
			cin >> x >> y >> k;
			// cout << "Copy " << x << " "  << y << " " << k << endl;
			// cout << "Update [" << y << " " << min(y + k + 1, N) << ")\n";
			update(sgtree, 1, 0, N, y, min(y + k + 1, N), x - y);
		}
		else { // kind == 2
			int i;
			cin >> i;
			// cout << "Query " << i << "\n";
			deltavalid dv = query(sgtree, 1, 0, N, i);
			// cout << dv.delta << (dv.valid ? " valid\n" : " invalid\n");
			if (dv.valid)
				cout << A[i + dv.delta] << endl;
			else
				cout << B[i] << endl;
		}
	}
	return 0;
}
