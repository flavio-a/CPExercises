// https://codeforces.com/contest/545/problem/C?locale=en
/*

Cuts from left to right, letting a tree fell in the first available between
left, right or not cutting it.

This is optimal: let's consider the first tree that doesn't fell, and let it be
at position i. The subarray from i + 1 onward doesn't have any bound that it
hadn't on the initial array, so it's exactly the same problem on a smaller
instance and thus by induction is solved optimally by this algorithm. The prefix
of the array is solved optimally: let L be the number of trees in the prefix:
given that the tree in i is the first not cut, in this subarray there were L - 1
trees cut, so the solution isn't optimal iff there's a way to cut all L trees,
but there isn't.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	int x[N + 1], h[N];
	for (int i = 0; i < N; ++i) {
		cin >> x[i] >> h[i];
	}
	x[N] = INT_MAX;
	// x[i] is already sorted by input hypothesis
	int count = 0;
	int mx = INT_MIN;
	for (int i = 0; i < N; ++i) {
		if (x[i] - h[i] >= mx) {
			// falling left
			++count;
			mx = x[i] + 1;
		}
		else if (x[i] + h[i] < x[i + 1]) {
			// falling right
			++count;
			mx = x[i] + h[i] + 1;
		}
		else {
			// not falling
			mx = x[i] + 1;
		}
	}
	cout << count << endl;
	return 0;
}
