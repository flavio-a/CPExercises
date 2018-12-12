// https://practice.geeksforgeeks.org/problems/longest-prefix-suffix/0
/*

Knuth-Morris-Pratt algorithm.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		string s;
		cin >> s;
		unsigned int P[s.length()];
		P[0] = 0;
		unsigned int k = 0;
		for (int q = 1; q < s.length(); ++q) {
			while (k > 0 && s[q] != s[k]) {
				k = P[k - 1];
			}
			if (s[q] == s[k]) {
				++k;
			}
			P[q] = k;
		}
		// for (int i = 0; i < s.length() - 1; ++i) {
		// 	cout << P[i] << " ";
		// }
		cout << P[s.length() - 1] << "\n";
	}
	return 0;
}
