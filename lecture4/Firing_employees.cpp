// https://practice.geeksforgeeks.org/problems/firing-employees/0
/*

Computes an array of primality with the sieve of Eratosthenes, then computes the
number of senior recursively by 1 plus the number of seniors of their senior,
storing the results in an array to avoid double computations.

The time complexity for anything but the sieve is Theta(N): the recursive
function is called for each index with it and its senior only (I can suppose
that when a call is done the senior is already stored, "swapping" the
computation with the actual call of the senior).
The time complexity of the sieve is O(N log log N), it's a well known result.
The space complexity is Theta(N) for the support arrays.

*/

#include <bits/stdc++.h>

using namespace std;

vector<bool> sieve_eratosthenes(int n) {
	n += 1; //to calc primes up to n included
	vector<bool> primes(n, true);
	primes[1] = false;
	int i = 2;
	while(i < sqrt(n)) {
		for (int j = i * i; j < n; j += i)
			primes[j] = false;
		while(!primes[++i]); // Get the next prime
	}
	return primes;
}

int calcNseniors(int i, int senior[], int nseniors[]) {
	if (nseniors[i] != 0 || senior[i] == 0)
		return nseniors[i];
	return nseniors[i] = 1 + calcNseniors(senior[i], senior, nseniors);
}

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;
		int senior[N + 1];
		for (int i = 1; i <= N; ++i) {
			int s;
			cin >> s;
			senior[i] = s;
		}

		int nseniors[N + 1] = {0};
		auto primes = sieve_eratosthenes(2 * N);
		// for (int i = 1; i < N + 1; ++i) {
		// 	cout << i << ": " << primes[i] << endl;
		// }
		int blacklisted = 0;
		for (int i = 1; i <= N; ++i) {
			// cout << i << " - " << calcNseniors(i, senior, nseniors) << endl;
			if (senior[i] != 0 && primes[i + calcNseniors(i, senior, nseniors)]) {
				++blacklisted;
				// cout << "Blacklisted " << i << " because " << i + nseniors[i] << endl;
			}
		}

		cout << blacklisted << endl;
	}
	return 0;
}
