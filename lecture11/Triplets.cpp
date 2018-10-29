// https://github.com/rossanoventurini/CompetitiveProgramming/blob/master/Exams/Text14022018.pdf
/*

Uses a Fenwick to compute an array pref[j] = #(i, j) such that i < j and
A[i] < A[j].
Using (implicitly) the array B[j] = n - A[n - 1 - j] computes the array
suff[j] = #(j, k) such that k > j and A[k] > A[j].
The result is then sum over j of pref[j] * suff[j].

Space complexity is Theta(n) for the Fenwick trees. Time complexity is
Theta(n log n) for the Fenwick.

*/

#include <bits/stdc++.h>

using namespace std;

#define lsb(x) (x & -x)

void update(vector<int> &ftree, int i, int val) {
	while (i < ftree.size()) {
		ftree[i] += val;
		i += lsb(i);
	}
}

int query(const vector<int> &ftree, int i) {
	int sum = 0;
	while (i != 0) {
		sum += ftree[i];
		i -= lsb(i);
	}
	return sum;
}

int main() {
	int N;
	cin >> N;
	int A[N];
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	vector<int> ftree(N, 0);
	long long int pref[N];
	for (int i = 0; i < N; ++i) {
		pref[i] = query(ftree, A[i] - 1);
		update(ftree, A[i], 1);
	}
	vector<int> ftree2(N, 0);
	long long int suff[N];
	for (int i = 0; i < N; ++i) {
		suff[N - 1 - i] = query(ftree2, N - A[N - 1 - i] - 1);
		update(ftree2, N - A[N - 1 - i], 1);
	}
	long long int result = 0;
	for (int i = 0; i < N; ++i)
		result += pref[i] * suff[i];
	cout << result << endl;
	return 0;
}
