// http://codeforces.com/problemset/problem/160/C?locale=en
/*

If the elements were all distinct, the k-th element of the sorted array of pairs
would be the pair made with the (k / n)-th element of the first array sorted and
the (k % n)-th element of the second array sorted.

Given that some kay may be repeated, a little adjustment is needed, that is to
divide by the number of repetition the index k of the pair, without considering
pairs starting with an element lower.

Time complexity is Theta(N * log N). Space complexity is Theta(1).

*/

#include <bits/stdc++.h>

using namespace std;

#define ull unsigned long long int

int main() {
	ull N, k;
	cin >> N >> k;
	// Index is 1-based
	--k;
	long long int A[N];
	for (ull i = 0; i < N; ++i)
		cin >> A[i];
	sort(A, A + N);
	// Needs the number of repetitions and of elements before A[k / N]
	ull lower = 0;
	while (A[lower] < A[k / N])
		++lower;
	ull reps = 0;
	while (A[lower + reps] == A[k / N] && reps < N)
		++reps;
	// All three cases are equal to (k - lower * N) / reps
	cout << A[k / N] << " " << A[(k - lower * N) / reps] << endl;
	return 0;
}
