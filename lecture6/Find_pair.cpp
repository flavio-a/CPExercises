// http://codeforces.com/problemset/problem/160/C?locale=en
/*

The k-th element of the sorted array of pairs is the pair made with the
(k / n)-th element of the first array sorted and the (k % n)-th element of the
second array sorted.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, k;
	cin >> N >> k;
	--k;
	int A[N];
	for (int i = 0; i < N; ++i) {
		int a;
		cin >> a;
		A[i] = a;
	}
	sort(A, A + N);
	cout << A[k / N] << " " << A[k % N] << endl;
	return 0;
}
