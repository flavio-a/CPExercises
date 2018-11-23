// https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room/0
/*

Algorithm seen at lecture. Takes greedily the first by ending time.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;
		int S[N], F[N];
		for (int i = 0; i < N; ++i)
			cin >> S[i];
		for (int i = 0; i < N; ++i)
			cin >> F[i];
		int indexes[N];
		iota(indexes, indexes + N, 0);
		sort(indexes, indexes + N, [&F](int a, int b) {
			return F[a] < F[b];
		});
		int lastIdx = indexes[0];
		cout << lastIdx << " ";
		for (int i = 0; i < N; ++i) {
			if (S[indexes[i]] >= F[lastIdx]) {
				lastIdx = indexes[i];
				cout << lastIdx + 1 << " ";
			}
		}
		cout << endl;
	}
	return 0;
}
