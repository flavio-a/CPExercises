// http://codeforces.com/problemset/problem/596/B?locale=en
/*

Each operation doesn't change elements from i - 1 backward, so the only way to
have a[1] == b[1] is to add b[1] - a[1] to position 1, and any operation
other than those won't change the correct value of a[1], so those operations are
necessary.
After this set of operation the problem is the very same on the array a[2 .. N]
that starts with all values equal to a[1] = b[1]. By induction, this is number
of operation is required.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	int actualVal = 0;
	unsigned long long int count = 0;
	int bi;
	for (int i = 0; i < N; ++i) {
		cin >> bi;
		count += abs(bi - actualVal);
		actualVal = bi;
	}
	cout << count << endl;
	return 0;
}
