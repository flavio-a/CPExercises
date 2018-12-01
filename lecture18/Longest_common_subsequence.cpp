// https://practice.geeksforgeeks.org/problems/longest-common-subsequence/0
/*

DP algorithm seen at lecture.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int a, b;
		cin >> a >> b;
		string s1, s2;
		cin >> s1 >> s2;
		unsigned int tab[s1.length() + 1][s2.length() + 1];
		for (int i = 0; i < s1.length() + 1; ++i) {
			tab[i][0] = 0;
		}
		// cout << "  ";
		for (int j = 0; j < s2.length() + 1; ++j) {
			tab[0][j] = 0;
			// cout << s2[j] << " ";
		}
		// cout << endl;
		for (int i = 1; i < s1.length() + 1; ++i) {
			// cout << s1[i - 1] << " ";
			for (int j = 1; j < s2.length() + 1; ++j) {
				unsigned int val = 0;
				if (s1[i - 1] == s2[j - 1]) {
					val = tab[i - 1][j - 1] + 1;
				}
				val = max(val, tab[i - 1][j]);
				val = max(val, tab[i][j - 1]);
				tab[i][j] = val;
				// cout << val << " ";
			}
			// cout << endl;
		}
		cout << tab[s1.length()][s2.length()] << endl;
	}
	return 0;
}
