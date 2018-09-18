// http://practice.geeksforgeeks.org/problems/leaders-in-an-array/0
#include <iostream>
#include <vector>

using namespace std;

int main(){
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t){
		int N;
		cin >> N;
		int A[N];
		// Read the array
		for (int i = 0; i < N; ++i) {
			int x;
			cin >> x;
			A[i] = x;
		}
		// Create a queue to reverse print
		vector<int> leaders;
		leaders.reserve(N);
		int max = A[N - 1];
		for (int i = N - 1; i >= 0; --i) {
			if (A[i] >= max) {
				leaders.push_back(A[i]);
				max = A[i];
			}
		}
		cout << leaders[leaders.size() - 1];
		for (int i = leaders.size() - 2; i >= 0; --i) {
			cout << ' ' << leaders[i];
		}
		cout << '\n';
	}

	return 0;
}
