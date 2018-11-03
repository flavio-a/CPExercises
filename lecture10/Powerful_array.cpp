// http://codeforces.com/contest/86/problem/D
// TODO
/*

Mo's algorithm.

*/

#include <bits/stdc++.h>

using namespace std;

inline long long int deltaPower(long long int counter, long long int val, long long int dir) {
	return val * (2 * dir * counter + 1);
}

int main() {
	int N, T;
	cin >> N >> T;
	long long int A[N];
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	int sqrtN = ceil(sqrt(N));
	pair<int, int> queries[T];
	int indexes[T];
	iota(indexes, indexes + T, 0);
	for (int t = 0; t < T; ++t) {
		int l, r;
		cin >> l >> r;
		// Indexes 1-based, correcting
		queries[t] = pair<int, int>(l - 1, r - 1);
	}
	// Sort queries sorted by (bucket; end)
	sort(indexes, indexes + T, [sqrtN, N, &queries](int i1, int i2) {
		auto p1 = queries[i1], p2 = queries[i2];
		if (p1.first / sqrtN == p2.first / sqrtN)
			return p1.second < p2.second;
		// Given that the two elements are in distinct buckets, it's enough to
		// compare the values of l
		return p1.first < p2.first;
	});

	// To apply Mo's algorithm, I need to keep track of how many occurences of
	// s are in the subarray
	unordered_map<int, int> occurrences;
	occurrences.reserve(N);
	// At some point each value of the array will be an index of the hashtable
	// To avoid checks after, let's initialize it now
	for (int i = 0; i < N; ++i)
		occurrences[A[i]] = 0;

	// Consider subarray A[l, r], ends included
	int l = 0, r = -1;

	long long int arraypow = 0;
	long long int results[T];
	for (int t = 0; t < T; ++t) {
		// cout << "Query " << indexes[t] << " [" << queries[indexes[t]].first << ", " << queries[indexes[t]].second << "]: ";
		while (r > queries[indexes[t]].second) {
			auto counter = occurrences.find(A[r]);
			arraypow += deltaPower((*counter).second, A[r], -1);
			--(*counter).second;
			--r;
		}
		// cout << "r- ";

		while (r < queries[indexes[t]].second) {
			++r;
			auto counter = occurrences.find(A[r]);
			arraypow += deltaPower((*counter).second, A[r], +1);
			++(*counter).second;
		}
		// cout << "r+ ";

		while (l > queries[indexes[t]].first) {
			--l;
			auto counter = occurrences.find(A[l]);
			arraypow += deltaPower((*counter).second, A[l], +1);
			++(*counter).second;
		}
		// cout << "l- ";

		while (l < queries[indexes[t]].first) {
			auto counter = occurrences.find(A[l]);
			arraypow += deltaPower((*counter).second, A[l], -1);
			--(*counter).second;
			++l;
		}
		// cout << "l+\n";
		results[indexes[t]] = arraypow;
	}

	for (int t = 0; t < T; ++t)
		cout << results[t] << "\n";

	return 0;
}
