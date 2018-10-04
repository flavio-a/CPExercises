// http://codeforces.com/problemset/problem/466/C?locale=en
/*

Computes a third of the total sum. If it isn't integer the answer is 0, else
computes an array with 1 if the prefix sum up to that index is equal to a third
of the total, else 0. In place of this array, it stores its array of prefix
sums, to allow queries in constant time. Now iterating over indexes from the end
and computing suffix sums get the job done.

Space complexity is Theta(n) for the prefix sums. Time complexity is Theta(n)
for each single operation, thus the total is Theta(n).

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	int A[n];
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		A[i] = a;
		sum += a;
	}
	if (sum % 3 != 0) {
		cout << 0 << endl;
		return 0;
	}
	int thirdsum = sum / 3;
	// Fills the prefix
	int prefs[n] = {0};
	int prefixsum = 0;
	for (int i = 0; i < n; ++i) {
		prefixsum += A[i];
		prefs[i] = prefs[i - 1];
		if (prefixsum == thirdsum)
			prefs[i]++;
	}

	int result = 0;
	int suffixsum = 0;
	for (int i = n - 1; i >= 0; --i) {
		suffixsum += A[i];
		if (suffixsum == thirdsum)
			result += prefs[i - 2];
	}
	cout << result << endl;
	return 0;
}
