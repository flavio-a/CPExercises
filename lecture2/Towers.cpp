// http://codeforces.com/problemset/problem/37/A?locale=en

#include <iostream>
#include <algorithm>

using namespace std;

int main(){
	const int max_length = 1000;

	int N;
	cin >> N;
	int T[max_length + 1];
	for (int i = 0; i < max_length + 1; ++i)
		T[i] = 0;
	int max = 0;
	int count = 0;
	// Read the array of heights
	for (int i = 0; i < N; ++i) {
		int x;
		cin >> x;
		if (T[x] == 0)
			++count;
		++T[x];
		if (T[x] > max)
			max = T[x];
	}

	cout << max << ' ' << count << '\n';

	return 0;
}
