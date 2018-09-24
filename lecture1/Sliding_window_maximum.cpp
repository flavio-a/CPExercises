// https://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/0
/*

Explanation of the algorithm:
using the deque, as seen at lesson.

*/
#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int main(){
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// Reading input
		int N, k;
		cin >> N;
		cin >> k;
		int A[N];
		for (int i = 0; i < N; ++i){
			int x;
			cin >> x;
			A[i] = x;
		}

		// Filling array of results, using the deque
		int R[N];
		deque<pair<int, int>> d;
		for (int i = 0; i < N; ++i) {
			// Remove the first element if is out of the window
			if (d.front().second <= i - k)
				d.pop_front();
			// Remove smaller elements from back
			while(!d.empty() && d.back().first < A[i])
				d.pop_back();
			// Get the front element as maximum and add the new element
			d.push_back(pair<int, int>(A[i], i));
			R[i] = d.front().first;
		}

		cout << R[k - 1];
		for (int i = k; i < N; ++i)
			cout << ' ' << R[i];
		cout << '\n';
	}

	return 0;
}
