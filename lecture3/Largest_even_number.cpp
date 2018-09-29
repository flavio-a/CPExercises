// https://practice.geeksforgeeks.org/problems/largest-even-number/0

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		string s;
		cin >> s;
		sort(s.begin(), s.end(), greater<char>());
		cout << s << endl;
		for (int i = s.length() - 1; i >= 0; --i) {
			if ((s[i] - '0') % 2 == 0) {
				char tmp = s[i];
				s[i] = s[s.length() - 1];
				s[s.length() - 1] = tmp;
				sort(s.begin(), s.end() - 1, greater<char>());
				break;
			}
		}
		cout << s << endl;
	}
	return 0;
}
