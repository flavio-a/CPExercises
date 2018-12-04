// https://practice.geeksforgeeks.org/problems/longest-bitonic-subsequence/0
/*

Slight variation of the DP algorithm seen at class.
Computes the LIS in prefixes and the LDS (longest decreasing subsequence) in
suffixes (that is, LIS on the reversed sequence). Note that this aren't
guaranteed to end exactly at i. The result is the maximum of LIS[i] + LDS[i - 1]
to ensure that the element i isn't counted twice in both LIS and LDS.

Space complexity is Theta(N) (to store LIS and LDS). Time complexity is the same
as LIS, so is O(N log N)

*/

#include <bits/stdc++.h>

using namespace std;

// Returns the maximum index i such that A[LIS[i]] < val
int binsearch(const vector<int> &LIS, int val, const vector<int> &A, int start, int end) {
	if (start + 1 == end) {
		return start;
	}
	int mid = (start + end) / 2;
	if (A[LIS[mid]] < val) {
		return binsearch(LIS, val, A, mid, end);
	}
	else {
		return binsearch(LIS, val, A, start, mid);
	}
}

vector<int> computeLIS(const vector<int> &A) {
	// This is the vector used in the algorithm to compute the actual LISs
	// and contains the index of the head of the dominating LIS of length i
	// The array with the LIS in the prefix is result
	vector<int> LIS;
	LIS.reserve(A.size());
	// the LIS of length 0 can always be extended
	LIS.push_back(INT_MIN);

	vector<int> result(A.size());
	for (int i = 0; i < A.size(); ++i) {
		int newidx = binsearch(LIS, A[i], A, 0, LIS.size());
		if (newidx + 1 == LIS.size()) {
			LIS.push_back(i);
		}
		else {
			LIS[newidx + 1] = i;
		}
		result[i] = LIS.size() - 1;
	}
	return result;
}

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;
		vector<int> A(N);
		for (int i = 0; i < N; ++i) {
			cin >> A[i];
		}
		vector<int> LIS = computeLIS(A);
		reverse(A.begin(), A.end());
		vector<int> LDS = computeLIS(A);
		reverse(LDS.begin(), LDS.end());
		int maxsum = LIS[0] + LDS[1];
		// cout << LIS[0] << " " << LDS[0] << endl;
		for (int i = 1; i < N - 1; ++i) {
			maxsum = max(maxsum, LIS[i] + LDS[i + 1]);
			// cout << LIS[i] << " " << LDS[i] << endl;
		}
		// cout << LIS[N - 1] << " " << LDS[N - 1] << endl;
		cout << maxsum << endl;
	}
	return 0;
}
