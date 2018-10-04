// https://www.spoj.com/problems/UPDATEIT/
/*

Given that all the updates happen before all the queries, the algorithm stores
the difference array, uses it to perform range updates in constant time (adding
and subtracting the value at the begin and at the end of the range), then
computes the original array by prefix sums, to support queries in constant time.

Space complexity is Theta(n), time complexity is Theta(u) for the update phase,
Theta(n) between the two phases to compute the prefix sums and Theta(q) to
answer queries. the total is Theta(u + n + q).

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N, U;
		cin >> N >> U;
		int diffArray[N] = {0};
		for (int u = 0; u < U; ++u) {
			int l, r, val;
			cin >> l >> r >> val;
			diffArray[l] += val;
			diffArray[r + 1] -= val;
		}
		int A[N];
		A[0] = diffArray[0];
		for (int i = 1; i < N; ++i) {
			A[i] = A[i - 1] + diffArray[i];
		}
		int Q;
		cin >> Q;
		for (int q = 0; q < Q; ++q) {
			int i;
			cin >> i;
			cout << A[i] << endl;
		}
	}
	return 0;
}
