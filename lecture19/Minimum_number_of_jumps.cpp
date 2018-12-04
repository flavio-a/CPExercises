// https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps/0
/*

DP algorithm: computes the solution for each position in the array up to N.
The solution R[i] for i is 1 + the minimum of R[j] for j < i and i - j <= a[j],
or 1 if no such j exists.

To improve this algorithm, let's use the following obsevation: fixed i, for any
j > i it holds R[j] >= R[i]. By absurd, let j be the minimum index > i with
R[j] < R[i]. By construction there must exixst a k < j with a[k] >= j - k and
R[k] = R[j] - 1 < R[i]. Given that j is the minimum index greater than i with
this property, it follows that k < i, thus R[i] <= 1 + R[k] = R[j] < R[i].

By this observation follows that the array is sorted, thus is formed by blocks
of consecutive elements with the same R. Let's consider the block of elements
with R[i] = V, and let's say is the interval [n; m]. Than the right end of the
block of R[i] = V + 1 must be <= than the maximum of i + a[i] where i iterates
over [n; m] because each element in that block must be reachable from an element
of the block V. Of course this upper bound is reached because from the index
that maximizes that quantity it is possible to reach any element in the range
[m + 1; i + a[i]].

To compute this is enough to traverse each block setting R[i] = V for that block
and keeping track of the maximum of i + a[i]; once the block is over increment V
and restart. Actually there's no need to store the full array R, it's enough to
store V.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;
		int A[N];
		for (int i = 0; i < N; ++i) {
			cin >> A[i];
		}
		int maxindex = A[0], i = 1, jumpnumber = 0;
		while (i < N) {
			++jumpnumber;
			int newmax = maxindex;
			for (; i <= maxindex; ++i) {
				if (newmax < i + A[i]) {
					newmax = i + A[i];
				}
			}
			maxindex = min(N, newmax);
		}
		cout << jumpnumber << endl;
	}
	return 0;
}
