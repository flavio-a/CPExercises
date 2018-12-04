// https://practice.geeksforgeeks.org/problems/longest-palindromic-subsequence/0
/*

Computes the LCS of the string and its reverse.

Time and space complexity are as in LCS, that is Theta(N ^ 2) (space can be
improved if there's no need to reconstruct the LCS).

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		string s1;
		cin >> s1;
		string s2;
		s2.resize(s1.size());
		copy(s1.begin(), s1.end(), s2.begin());
		reverse(s2.begin(), s2.end());
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
