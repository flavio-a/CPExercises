// https://practice.geeksforgeeks.org/problems/kadanes-algorithm/0
#include <iostream>

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
		int sum = A[0];
		int max = sum;
		for (int i = 1; i < N; ++i){
			if (sum > 0)
				sum += A[i];
			else
				sum = A[i];
			if (sum > max)
				max = sum;
		}
		cout << max << '\n';
	}

	return 0;
}
