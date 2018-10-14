// http://codeforces.com/problemset/problem/353/B?locale=en
/*

To maximize the number of distinct four-digits numbers the algorithm splits
equal numbers as evenly as possible.

First of all, computes the sum of the number of duplicates minus two, that is
used to compute the number of possible four digits numbers.

To split the numbers consider three cases: numbers that apears once, that
appears an even and an odd number of times. The last case is handled treating
one of the element with that value as a placeholder and the others as an element
appearing an even number of times; this case is handled simply splitting evenly
the occurences between the two heaps. In the end, single number are split evenly
between the two heaps. After this, the placeholders fills the space.

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
	dati A[2 * N] = {0};
	int freq[100] = {0};
	int totrep = 0;
	for (int i = 0; i < 2 * N; ++i) {
		int a;
		cin >> a;
		A[i].val = a;
		if (freq[a] > 1)
			++totrep;
		++freq[a];
	}
	// Totrep is the number of duplicate numbers minus 2
	int tmp = 2 * N - totrep;
	cout << (tmp / 2) * (tmp - tmp / 2) << endl;

	int heaps[2] = {N, N};
	// Marks placeholders updating the heaps count (the actual insertion is in
	// the next cycle)
	bool added[100] = {false};
	for (int i = 0; i < 2 * N; ++i) {
		if (freq[A[i].val] > 1 && !added[A[i].val]) {
			if (freq[A[i].val] % 2 == 1) {
				--freq[A[i].val];
				A[i].val += 100;
			}
			heaps[0] -= freq[A[i].val] / 2;
			heaps[1] -= freq[A[i].val] / 2;
			added[A[i].val] = true;
			freq[A[i].val] += 2; // To split more easily
		}
	}

	// Splits evenly repeated numbers (now all repeated numbers) and
	// non-placeholders
	for (int i = 0; i < 2 * N; ++i) {
		if (A[i].val >= 100) {
			// Placeholder
		}
		else if (freq[A[i].val] > 1) {
			// Repeated
			A[i].heap = freq[A[i].val] % 2;
			--freq[A[i].val];
		}
		else {
			// Non-placeholder
			if (heaps[0] < heaps[1]) {
				A[i].heap = 1;
				--heaps[1];
			}
			else {
				A[i].heap = 0;
				--heaps[0];
			}
		}
	}

	// Printing. Placeholders are put in a heap here
	for (int i = 0; i < 2 * N; ++i) {
		if (A[i].val >= 100) {
			// Placeholder
			if (heaps[0] > 0) {
				cout << 1 << " ";
				--heaps[0];
			}
			else
				cout << 2 << " ";
		}
		else {
			cout << A[i].heap + 1 << " ";
		}
	}
	cout << endl;
	return 0;
}
