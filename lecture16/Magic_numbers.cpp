// http://codeforces.com/problemset/problem/320/A?locale=en
/*

Greedy algorithm: checks if the substring starting at i matches one of the three
allowed. It it does, it increments i of the right value. Substrings are tested
in order of length because otherwise it wouldn't work.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	string n = to_string(N);
	int i = 0;
	while (i < n.length()) {
		if (n.substr(i, 3).compare("144") == 0) {
			i += 3;
		}
		else if (n.substr(i, 2).compare("14") == 0) {
			i += 2;
		}
		else if (n.substr(i, 1).compare("1") == 0) {
			i += 1;
		}
		else {
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	return 0;
}
