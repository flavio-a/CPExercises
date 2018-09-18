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
		int N;
		cin >> N;
		int A[N];
		for (int i = 0; i < N; ++i){
			int x;
			cin >> x;
			A[i] = x;
		}

		// Filling array of results, using the deque
		// TODO (WIP)
		int R[N];
		deque<int> d;
		for (int i = 0; i < N; ++i) {
			while(!d.empty() && d.front() < A[i]) {
				d.pop_front();
			}
			R[i] = d.empty() ? -1 : d.front();
			d.push_front(pair<int, int>(A[i], i));
		}

		cout << R[0];
		for (int i = 1; i < N; ++i)
			cout << ' ' << R[i];
		cout << '\n';
	}

	return 0;
}
