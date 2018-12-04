// https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence/0
/*

DP algorithm seen at class, improved as seen in the link.
Recall: i dominates j iff LIS[i] >= LIS[j] and A[i] <= A[j].

The BST contains at most (actually exactly, but that's not important) one
element for each possible value of LIS, so it can be replaced with an array
using LIS as indexes. This is because if two element has the same LIS there must
be one with lower A[i], and we're only keeping that.
The key observation is that when LIS[i] > LIS[j] it holds A[i] > A[j], otherwise
i would dominate j and thus we would remove j from the array of not dominated
indexes. Thus the array storing A[i] at index LIS[i] is sorted.
This allows us to use binary search on that array to find the biggest value
lower than a certain A[k], whose index is the maximum LIS that can be extended
with A[k].
Actually the implementation stores i at index LIS[i]. It traverses A, and adds
A[i] as the head of the longest LIS (up to i - 1) that can be extended with A[i]
(that is, ends with a lower value). This allows to replace the LIS with one more
element because it's dominated (it must holds that it's head is >= A[i] because
the previous LIS it the highest lower than A[i]).

Time complexity is O(N log N) because for each element of A it performs a binary
search on an array of at most N elements. Space complexity is O(N) for the LIS
array.

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
		vector<int> LIS;
		LIS.reserve(N);
		// the LIS of length 0 can always be extended
		LIS.push_back(INT_MIN);
		for (int i = 0; i < N; ++i) {
			int newidx = binsearch(LIS, A[i], A, 0, LIS.size());
			// // DEBUG
			// for (int j = 0; j < LIS.size(); ++j) {
			// 	cout << LIS[j] << " ";
			// }
			// cout << endl << newidx << endl;
			// // END DEBUG
			if (newidx + 1 == LIS.size()) {
				LIS.push_back(i);
			}
			else {
				LIS[newidx + 1] = i;
			}
		}
		// The highest index in the array is the highest value for which there
		// exists a LIS of that length
		cout << LIS.size() - 1 << endl;
	}
	return 0;
}
