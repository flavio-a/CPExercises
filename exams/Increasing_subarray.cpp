/*

Keeps two values: the max with the actual increasing subarray concatenated with
the penultimate, and the actual alone. The result is the maximum of all these.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	int A[N + 1];
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	A[N] = INT_MIN;

	int result = -1;
	int single_s = 1, double_s = 1;
	for (int i = 1; i < N; ++i) {
		if (A[i - 1] < A[i]) {
			++single_s;
			++double_s;
		}
		else {
			if (A[i - 1] < A[i + 1] - 1) {
				double_s = single_s + 1;
				single_s = 1;
			}
			else {
				double_s = 2;
				single_s = 1;
			}
		}
		result = max(result, max(single_s, double_s));
		// cout << "Index " << i << ": single = " << single_s << ", double = " << double_s << endl;
	}
	cout << result << endl;

	return 0;
}
