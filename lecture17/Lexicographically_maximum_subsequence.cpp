// http://codeforces.com/problemset/problem/196/A?locale=en
/*

First of all it reverse scan the sequence to build an array of the greatest
letter in its suffix.
With this info, it starts the greedy algorithm: takes any letter equals to the
greatest in the suffix, and discard others.

Let's proof that it is optimal: suppose that at some point I take the element C
that isn't the maximum of its suffix. Let's consider the subsequence that is
equal to the considered subsequence up to C but that takes the maximum of the
suffix in place of C. This subsequence is lexicographically larger than the one
consider, thus the absurd. Conversely, if at some point I don't take C that is
the maximum of its suffix, the subsequence that takes exactly the same elements
and C is larger.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	string s;
	cin >> s;
	int N = s.length();
	char maxsuff[N];
	maxsuff[N - 1] = s[N - 1];
	for (int i = N - 2; i >= 0; --i) {
		maxsuff[i] = max(maxsuff[i + 1], s[i]);
	}
	for (int i = 0; i < N; ++i) {
		if (s[i] == maxsuff[i])
			cout << s[i];
	}
	cout << endl;
	return 0;
}
