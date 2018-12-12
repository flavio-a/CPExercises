// https://www.codechef.com/problems/TASHIFT
/*

I create a string concatenating B with itself, then search in it the longest
prefix of A as a substring. This is performed in linear time in the sum of the
two lengths with the following algorithm:
let S = A + "$" + B + B, where $ is a character that isn't in A nor in B. I keep
an array P as long as S with the meaning that P[i] = length of the longest
prefix of S that starts at S[i]. To compute this array I traverse S this way: I
keep track of a starting point start (initially 1) that tells me where does the
prefix of S I'm matching begins. I increment i until I get a mismatch between
the prefix of S and the substring beginning at start. At this point (i - start)
is the length of the longest common prefix starting at S[start], and I can copy
P[0..] into P[start..] until I find a value of j > start such that
j + P[j - start] is at least i. In this case I have a new prefix matching up to
i - 1, and can continue the standard iteration with j as the new value of start.

The answer is the index in B of the max in P.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	string A, B;
	cin >> A >> B;

	auto S = [&N, &A, &B](int i) {
		if (i < N) {
			return A[i];
		}
		if (i == N) {
			return '$';
		}
		return B[(i - 1) % N];
	};
	unsigned int P[3 * N + 1];
	P[0] = 3 * N + 1;
	// currently matching prefix starts at start
	int start = 1, i = 1;
	while (i < 3 * N + 1) {
		if (S(i) == S(i - start)) {
			// Match, enlarge the previous longest prefix
			++i;
		}
		else {
			// Mismatch, the prefix up to i - 1 is the longest from start
			P[start] = i - start;
			// Start copying P until it find another match for the prefix
			int j = start + 1;
			while (j + P[j - start] < i && j < 3 * N + 1) {
				P[j] = P[j - start];
				++j;
			}
			start = j;
			if (start > i) {
				i = start;
			}
		}
	}
	P[start] = i - start;
	// Start copying P until it find another match for the prefix
	int j = start + 1;
	while (j + P[j - start] < i && j < 3 * N + 1) {
		P[j] = P[j - start];
		++j;
	}

	// for (int i = 0; i < 3 * N + 1; ++i) {
	// 	cout << S(i) << " ";
	// }
	// cout << "\n  ";
	// for (int i = 1; i < 3 * N + 1; ++i) {
	// 	cout << P[i] << " ";
	// }
	// cout << "\n";

	int pos = N + 1;
	for (int i = pos + 1; i < 3 * N + 1; ++i) {
		if (P[pos] < P[i] || (P[pos] == P[i] && ((pos - N - 1) % N) < ((i - N - 1) % N))) {
			pos = i;
		}
	}
	cout << (pos - N - 1) % N << endl;
	return 0;
}
