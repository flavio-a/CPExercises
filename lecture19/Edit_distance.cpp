// https://practice.geeksforgeeks.org/problems/edit-distance/0
/*

DP algorithm seen at class.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int n, m;
		cin >> n >> m;
		string s1, s2;
		cin >> s1 >> s2;
		unsigned int R[n + 1][m + 1];
		for (int i = 0; i < n + 1; ++i) {
			R[i][0] = i;
		}
		for (int j = 0; j < m + 1; ++j) {
			R[0][j] = j;
		}
		for (int i = 1; i < n + 1; ++i) {
			for (int j = 1; j < m + 1; ++j) {
				if (s1[i] == s2[j]) {
					R[i][j] = R[i - 1][j - 1];
				}
				else {
					R[i][j] = 1 + min(R[i - 1][j], min(R[i - 1][j - 1], R[i][j - 1]));
				}
			}
		}
		cout << R[n][m] << endl;
	}
	return 0;
}
