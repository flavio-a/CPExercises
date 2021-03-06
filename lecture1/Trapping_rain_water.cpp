// https://practice.geeksforgeeks.org/problems/trapping-rain-water/0
/*

Explanation of the algorithm:
Studying a single column at a time, the height of water in that column is the
minimum of the right and left maximums (the maximum of elements to the
right/left of the column). Right maximums (or suffix maximums) are computed
before and stored in an array, then the main cycle sums the amount of water
(0 or the difference between water height and building height) in each column.

Both time and space complexity are Theta(n).

*/
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t){
		int N;
		cin >> N;
		int A[N];
		// Read the array of heights
		for (int i = 0; i < N; ++i) {
			int x;
			cin >> x;
			A[i] = x;
		}

		// Calcs the array of suffix maximums
		int maxSuff[N];
		maxSuff[N - 1] = 0;
		for (int i = N - 2; i >= 0; --i){
			if (A[i + 1] > maxSuff[i + 1])
				maxSuff[i] = A[i + 1];
			else
				maxSuff[i] = maxSuff[i + 1];
			// cout << "maxSuff " << i << ": " << maxSuff[i] << endl;
		}

		int water = 0;
		int maxPref = 0;
		for (int i = 0; i < N; ++i){
			// cout << i << ' ' << min(maxPref, maxSuff[i]) - A[i] << '\n';
			water += max(0, min(maxPref, maxSuff[i]) - A[i]);
			if (A[i] > maxPref)
				maxPref = A[i];
		}

		cout << water << '\n';
	}

	return 0;
}
