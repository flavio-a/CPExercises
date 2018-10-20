// http://codeforces.com/problemset/problem/459/D?locale=en
/*

Precomputes two arrays, S[i] = f(1, i, a_i) and E[i] = f(j, n, a_j). Those
computations may be done in linear time keeping in an hashtable the number of
elements equal to a_i already found while scanning the array.

Now we want the sum over j of the number of i-s so that i < j and S[i] > E[j];
this can be computed with a Fenwick tree updated while iterating over j,
querying at E[j] and then adding 1 to S[j]. Given that the array has size N,
S[j] and E[i] are at most N.

Time complexity is Theta(N * log N) for the iteration with queries on the
Fenwick tree. Space complexity is Theta(N) for the Fenwick itself.

*/

#include <bits/stdc++.h>

using namespace std;

#define lsb(x) (x & -x)

void update(vector<int> &v, int i, int x) {
	while (i < v.size()) {
		v[i] += x;
		i += lsb(i);
	}
}

int query(const vector<int> &v, int i) {
	int sum = 0;
	while (i > 0) {
		sum += v[i];
		i -= lsb(i);
	}
	return sum;
}

int main() {
	unsigned long long int N;
	cin >> N;
	vector<int> A(N);
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	int S[N];
	unordered_map<int, int> elem_count;
	elem_count.reserve(N);
	for (int i = 0; i < N; ++i) {
		auto count = elem_count.find(A[i]);
		if (count == elem_count.end()) {
			// Count == 0
			S[i] = 0;
			elem_count[(A[i])] = 1;
		}
		else {
			S[i] = (*count).second;
			(*count).second += 1;
		}
	}
	int E[N];
	elem_count.clear();
	elem_count.reserve(N);
	for (int i = N - 1; i >= 0; --i) {
		auto count = elem_count.find(A[i]);
		if (count == elem_count.end()) {
			// Count == 0
			E[i] = 0;
			elem_count[(A[i])] = 1;
		}
		else {
			E[i] = (*count).second;
			(*count).second += 1;
		}
	}

	// for (int i = 0; i < N; ++i) {
	// 	cout << S[i] << "	" << E[i] << endl;
	// }

	vector<int> ftree(N + 1, 0);
	long long int result = 0;
	for (int j = 0; j < N; ++j) {
		// The query is the number of i < j so that S[j] <= E[j]
		result += query(ftree, E[j] + 1);
		update(ftree, S[j] + 1, 1);
	}
	result = ((N * (N - 1)) / 2) - result;
	cout << result << endl;

	return 0;
}
