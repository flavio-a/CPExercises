// https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps/0
// TODO
/*

DP algorithm: the solution for position i is 1 + the minimum of the solutions in
i + 1, i + 2, ..., i + A[i].

*/

#include <bits/stdc++.h>

using namespace std;

int getmin(int dp[], int N, int i, int Ai) {
	int upbound = min(N, i + Ai) + 1;
	int res = dp[i + 1];
	for (int j = i + 2; j < upbound; ++j) {
		res = min(res, dp[j]);
	}
	return res;
}

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
		int dp[N + 1];
		dp[N] = 0;
		for (int i = N - 1; i >= 0; --i) {
			dp[i] = 1 + getmin(dp, N, i, A[i]);
		}
		// for (int i = 0; i < N; ++i)
		// 	cout << dp[i] << " ";
		cout << dp[0] << endl;
	}
	return 0;
}
