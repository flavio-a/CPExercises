// http://codeforces.com/problemset/problem/276/C?locale=en
/*

During the query phase, the program keeps the number of time an element appears
in a query, simply adding 1 to a counter array in the corresponding position. At
the end it sorts the initial array and the counter array, then returns the zip
of the two arrays with multiplication. The answer is obviously the zip of a
permutation of those two arrays, and that is the maximum because of
rearrangement ineq (https://en.wikipedia.org/wiki/Rearrangement_inequality).

The counter array is computed as in the update_the_array problem (the situation
is the same).

Space complexity is Theta(n). Time complexity is Theta(q) for the query phase,
Theta(n) for the intermediate phase and Theta(n log(n)) for the sorting +
zipping phase, for a total of Theta(n log(n) + q).

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, Q;
	cin >> N >> Q;
	long long int A[N];
	for (int i = 0; i < N; ++i) {
		int a;
		cin >> a;
		A[i] = a;
	}
	int diffArray[N] = {0};
	// vector<int> ftree(N + 1, 0);
	for (int q = 0; q < Q; ++q) {
		int l, r;
		cin >> l >> r;
		// Inputs are in a 1-based array
		--l;
		--r;
		diffArray[l] += 1;
		// r + 1 because r is included in te query
		diffArray[r + 1] -= 1;
	}
	long long int M[N];
	M[0] = diffArray[0];
	for (int i = 1; i < N; ++i) {
		M[i] = M[i - 1] + diffArray[i];
	}

	sort(A, A + N);
	sort(M, M + N);
	long long int sum = 0;
	for (int i = 0; i < N; ++i) {
		sum += A[i] * M[i];
	}
	cout << sum << endl;
	return 0;
}
