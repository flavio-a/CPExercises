// http://codeforces.com/problemset/problem/579/B?locale=en
/*

Explanation of the algorithm:
Creates triples (power, i, j), sorts them by power and takes in order of
highest power (of course both players in a tuple should be free in order for it
to be taken).

*/

#include <bits/stdc++.h>

using namespace std;

int main(){
	int N;
	cin >> N;
	N *= 2;

	vector<tuple<int, int, int>> teams;
	teams.reserve(N * (N-1) / 2);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j < i; ++j) {
			int a;
			cin >> a;
			teams.push_back(make_tuple(a, i, j));
		}
	}
	sort(teams.begin(), teams.end(), greater<tuple<int, int, int>>());

	int teammates[N + 1] = {};
	for (auto team: teams) {
		if (teammates[get<1>(team)] == 0 && teammates[get<2>(team)] == 0) {
			teammates[get<1>(team)] = get<2>(team);
			teammates[get<2>(team)] = get<1>(team);
		}
	}

	for (int i = 1; i <= N; ++i) {
		cout << teammates[i] << " ";
	}
	cout << endl;

	return 0;
}
