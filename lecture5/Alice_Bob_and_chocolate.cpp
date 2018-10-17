// http://codeforces.com/problemset/problem/6/C?locale=en
/*

Simulates the eating: keeps indexes and time of A and B, when timeA is lower
A starts eating a new bar, else B starts. Ends when they are both eating the
same bar. The only problem is when the two times are equals, so Alice sohuld
start eating the middle bar, that is handled by the final if.

Space is Theta(1), time is Theta(n).

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	int T[N];
	for (int i = 0; i < N; ++i) {
		int t;
		cin >> t;
		T[i] = t;
	}
	int timeA = 0, timeB = 0;
	int iA = 0, iB = N - 1;
	while (iA <= iB) {
		if (timeA <= timeB) {
			// cout << "A eats " << T[iA] << ", number " << iA << "\n";
			timeA += T[iA];
			++iA;
		}
		else {
			// cout << "B eats " << T[iB] << ", number " << iB << "\n";
			timeB += T[iB];
			--iB;
		}
	}
	// if (timeA == timeB) {
	// 	++iA;
	// 	++iB;
	// }
	++iB;
	cout << iA << " " << N - iB << endl;
	return 0;
}
