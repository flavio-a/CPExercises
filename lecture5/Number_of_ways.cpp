// http://codeforces.com/problemset/problem/466/C?locale=en
/*

Computes a third of the total sum. If it isn't integer the answer is 0, else
computes an array with 1 if the prefix sum up to that index is equal to a third
of the total, else 0. Stores this array in a Fenwick, and uses it to computes
the number of indexes with prefix sum equal to a third lower than a certain
index. Now iterating over indexes from the end and computing suffix sums get
the job done.

Space complexity is Theta(n) for the Fenwick tree. Time complexity is Theta(n)
to initialize the Fenwick, O(n log(n)) to fill the Fenwick and again O(n log(n))
when computing suffix sums and querying the Fenwick.

*/

#include <bits/stdc++.h>

using namespace std;

#define lsb(x) (x & -x)

void addVal(vector<int>& v, int i, int x) {
	while (i < v.size()) {
		v[i] += x;
		i += lsb(i);
	}
}

int getSum(const vector<int>& v, int i) {
	int result = 0;
	while (i > 0) {
		result += v[i];
		i -= lsb(i);
	}
	return result;
}

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
	// Fills the Fenwick tree
	vector<int> ftree(n + 1, 0);
	int prefixsum = 0;
	for (int i = 0; i < n; ++i) {
		prefixsum += A[i];
		if (prefixsum == thirdsum)
			addVal(ftree, i + 1, 1);
	}

	int result = 0;
	int suffixsum = 0;
	for (int i = n - 1; i >= 0; --i) {
		suffixsum += A[i];
		if (suffixsum == thirdsum)
			result += getSum(ftree, (i - 2) + 1);
	}
	cout << result << endl;
	return 0;
}
