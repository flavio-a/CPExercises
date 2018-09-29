// https://www.spoj.com/problems/INVCNT/
/*

Counts inversions during mergesort.

*/

#include <bits/stdc++.h>

using namespace std;

pair<int, vector<int>> merge_count(vector<int> A) {
	if (A.size() <= 1)
		return make_pair(0, A);

	int half = A.size() / 2;
	auto p1 = merge_count(vector<int>(A.begin(), A.begin() + half));
	auto p2 = merge_count(vector<int>(A.begin() + half, A.end()));
	int result = p1.first + p2.first;
	auto v1 = p1.second;
	auto v2 = p2.second;

	vector<int> B;
	B.reserve(A.size());
	unsigned int i = 0, j = 0;
	while (i < v1.size() || j < v2.size()) {
		if (j == v2.size()) {
			// Takes from first half, result unchanged
			B.push_back(v1[i]);
			++i;
		}
		else if (i == v1.size() || v1[i] > v2[j]) {
			// Takes from second half, increments result
			B.push_back(v2[j]);
			++j;
			result += v1.size() - i;
		}
		else {
			// Takes from first half, result unchanged
			B.push_back(v1[i]);
			++i;
		}
	}
	return make_pair(result, B);
}

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;
		vector<int> A;
		A.reserve(N);
		for (int i = 0; i < N; ++i) {
			int a;
			cin >> a;
			A.push_back(a);
		}

		cout << merge_count(A).first << endl;
	}
	return 0;
}
