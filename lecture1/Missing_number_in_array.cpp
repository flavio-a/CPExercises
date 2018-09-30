// https://practice.geeksforgeeks.org/problems/missing-number-in-array/0
/*

Keeps the sum modulo N of the array; the missing number is the one that gives
the right sum modulo N in the end (that is N - sum if N is odd, else is ).
Time complexity is Theta(N). Space complexity is Theta(log(N)) not assuming the
representation of integers constant.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;
		// There's no need to store the actual array
		int sum = 0;
		for (int i = 0; i < N - 1; ++i) {
			int a;
			cin >> a;
			sum = (sum + a) % N;
		}
		if (N % 2 == 1)
			cout << N - sum << endl;
		else {
			int r = (N + N / 2 - sum) % N;
			cout << (r == 0 ? N : r) << endl;
		}
	}
	return 0;
}
