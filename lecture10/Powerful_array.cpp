// http://codeforces.com/contest/86/problem/D
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
	// Remap A elements to 0..N - 1 in order to use an array instead of an
	// hashmap to keep the number of occurrences
	unordered_map<int, int> valToIndexes;
	valToIndexes.reserve(N);
	int Aindexes[N];
	int idx = 0;
	for (int i = 0; i < N; ++i) {
		if (valToIndexes.find(A[i]) == valToIndexes.end()) {
			valToIndexes[A[i]] = idx;
			++idx;
		}
		Aindexes[i] = valToIndexes[A[i]];
	}

	// Buckets division
	int sqrtN = ceil(sqrt(N));
	pair<int, int> queries[T];
	int Qindexes[T];
	iota(Qindexes, Qindexes + T, 0);
	for (int t = 0; t < T; ++t) {
		int l, r;
		cin >> l >> r;
		// Indexes 1-based, correcting
		queries[t] = pair<int, int>(l - 1, r - 1);
	}
	// Sort queries sorted by (bucket; end)
	sort(Qindexes, Qindexes + T, [sqrtN, N, &queries](int i1, int i2) {
		auto p1 = queries[i1], p2 = queries[i2];
		if (p1.first / sqrtN == p2.first / sqrtN)
			return p1.second < p2.second;
		// Given that the two elements are in distinct buckets, it's enough to
		// compare the values of l
		return p1.first < p2.first;
	});


	// To apply Mo's algorithm, I need to keep track of how many occurences of
	// s are in the subarray
	int occurrences[N] = {0};

	// Consider subarray A[l, r], ends included
	int l = 0, r = -1;

	long long int arraypow = 0;
	long long int results[T];
	for (int t = 0; t < T; ++t) {
		if (r > queries[Qindexes[t]].second) {
			// Finished bucket, resetting
			l = queries[Qindexes[t]].first;
			r = l - 1;
			arraypow = 0;
			for (int i = 0; i < N; ++i)
				occurrences[i] = 0;
		}

		while (r < queries[Qindexes[t]].second) {
			++r;
			arraypow += deltaPower(occurrences[Aindexes[r]], A[r], +1);
			++(occurrences[Aindexes[r]]);
		}

		while (l > queries[Qindexes[t]].first) {
			--l;
			arraypow += deltaPower(occurrences[Aindexes[l]], A[l], +1);
			++(occurrences[Aindexes[l]]);
		}

		while (l < queries[Qindexes[t]].first) {
			arraypow += deltaPower(occurrences[Aindexes[l]], A[l], -1);
			--(occurrences[Aindexes[l]]);
			++l;
		}
		results[Qindexes[t]] = arraypow;
	}

	for (int t = 0; t < T; ++t)
		cout << results[t] << "\n";

	return 0;
}
