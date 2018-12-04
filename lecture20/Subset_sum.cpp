// https://practice.geeksforgeeks.org/problems/subset-sum-problem/0
/*

DP algorithm seen at class.

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
		int sum = 0;
		for (int i = 0; i < N; ++i) {
			cin >> A[i];
			sum += A[i];
		}
		if (sum % 2 == 1) {
			cout << "NO\n";
		}
		else {
			sum = sum / 2;
			bool R[N + 1][sum + 1] = {false};
			for (int i = 0; i < N + 1; ++i) {
				R[i][0] = true;
			}
			for (int i = 1; i < N + 1; ++i) {
				for (int j = 0; j < sum + 1; ++j) {
					R[i][j] = R[i - 1][j];
					if (j - A[i] >= 0) {
						R[i][j] |= R[i - 1][j - A[i]];
					}
				}
			}
			cout << (R[N][sum] ? "YES" : "NO") << "\n";
		}
	}
	return 0;
}
