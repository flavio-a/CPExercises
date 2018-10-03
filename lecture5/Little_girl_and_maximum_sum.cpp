// http://codeforces.com/problemset/problem/276/C?locale=en
/*

During the query phase, the program keeps the number of time an element appears
in a query, simply adding 1 to a counter array in the corresponding position. At
the end it sorts the initial array and the counter array, then returns the zip
of the two arrays with multiplication. The answer is obviously the zip of a
permutation of those two arrays, and that is the maximum because of
rearrangement ineq (https://en.wikipedia.org/wiki/Rearrangement_inequality).

To compute efficiently the counter array it uses a Fenwick tree on the
difference array (see update the array problem).

Space complexity is Theta(n) (the Fenwick). Tme complexity is O(q * log(n)) for
the query phase and Theta(n log(n)) for the sorting + zipping phase.

*/

#include <bits/stdc++.h>

using namespace std;

// ================== Taken from Update the array code ======================
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
// ==========================================================================

int main() {
	int N, Q;
	cin >> N >> Q;
	int A[N];
	for (int i = 0; i < N; ++i) {
		int a;
		cin >> a;
		A[i] = a;
	}
	vector<int> ftree(N + 1, 0);
	for (int q = 0; q < Q; ++q) {
		int l, r;
		cin >> l >> r;
		// Inputs are in a 1-based array
		--l;
		--r;
		addVal(ftree, l + 1, 1);
		// r + 1 because r is included in te query
		addVal(ftree, (r + 1) + 1, -1);
	}
	int M[N];
	for (int i = 0; i < N; ++i) {
		M[i] = getVal(ftree, i + 1);
	}
	sort(A, A + N);
	sort(M, M + N);
	int sum = 0;
	for (int i = 0; i < N; ++i) {
		sum += A[i] * M[i];
	}
	cout << sum << endl;
	return 0;
}
