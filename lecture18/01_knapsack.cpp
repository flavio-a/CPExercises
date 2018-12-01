// https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem/0
/*

DP algorithm seen at lecture.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N, W;
		cin >> N >> W;
		++W;
		int v[N], w[N];
		for (int i = 0; i < N; ++i) {
			cin >> v[i];
		}
		for (int i = 0; i < N; ++i) {
			cin >> w[i];
		}
		int tab[N + 1][W];
		// cout << " | ";
		for (int j = 0; j < W; ++j) {
			tab[0][j] = 0;
			// cout << j << " ";
		}
		// cout << endl;
		for (int i = 1; i < N + 1; ++i) {
			// cout << i << "| ";
			for (int j = 0; j < W; ++j) {
				if (j - w[i - 1] >= 0) {
					tab[i][j] = max(tab[i - 1][j], tab[i - 1][j - w[i - 1]] + v[i - 1]);
				}
				else {
					tab[i][j] = tab[i - 1][j];
				}
				// cout << tab[i][j] << " ";
			}
			// cout << endl;
		}
		cout << tab[N][W - 1];
	}
	return 0;
}
