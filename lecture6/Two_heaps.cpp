// http://codeforces.com/problemset/problem/353/B?locale=en
// TODO
/*

To maximize the number of distinct four-digits numbers the algorithm splits
equal numbers as evenly as possible.

*/

#include <bits/stdc++.h>

using namespace std;

struct dati {
	int val;
	int heap;
};

int main() {
	int N;
	cin >> N;
	dati A[2 * N];
	int freq[101] = {0};
	int h[2] = {N, N};
	int toReverse = 0;
	for (int i = 0; i < 2 * N; ++i) {
		int a;
		cin >> a;
		A[i].val = a;
		if (freq[a] > 1) {
			if (toReverse == 0)
				toReverse = a;
			if (toReverse == a) {
				A[i].heap = (freq[a] + 1) % 2;
				--h[(freq[a] + 1) % 2];
			}
			else {
				A[i].heap = freq[a] % 2;
				--h[freq[a] % 2];
			}
		}
		++freq[a];
	}
	return 0;
}
