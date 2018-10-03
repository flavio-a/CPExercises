// https://www.spoj.com/problems/UPDATEIT/
/*

The Fenwick tree allows for range queries and point update. To allow point
queries and range updates I simply create the Fenwick tree on the difference
array.

Space complexity is Theta(n), time complexity is 2u+q operations on the Fenwick
tree plus the Fenwik intialization, so O(n + (u + q) * log(n))

*/

#include <bits/stdc++.h>

using namespace std;

#define lsb(x) (x & -x)

// Returns the element at index i of the array, that is the sum from 0 to i
// in the difference array, that is the query on the Fenwick tree
int getVal(vector<int>& v, int i) {
	int sum = 0;
	while (i != 0) {
		sum += v[i];
		i -= lsb(i);
	}
	return sum;
}

// Adds x to all elements from i (included) onward, that is the edit of i in the
// difference array, that is the update on the Fenwick tree
void addVal(vector<int>& v, int i, int x) {
	while (i < v.size()) {
		v[i] += x;
		i += lsb(i);
	}
}

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N, U;
		cin >> N >> U;
		vector<int> ftree(N + 1, 0);
		for (int u = 0; u < U; ++u) {
			int l, r, val;
			cin >> l >> r >> val;
			// The indexes are incremented by one because Fenwick trees starts
			// at 1
			addVal(ftree, l + 1, val);
			addVal(ftree, r + 1 + 1, -val);
		}
		// for (auto i: ftree) {
		// 	cout << i << " ";
		// }
		// cout << endl;
		int Q;
		cin >> Q;
		for (int q = 0; q < Q; ++q) {
			int i;
			cin >> i;
			cout << getVal(ftree, i + 1) << endl;
		}
	}
	return 0;
}
