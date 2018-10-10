// http://codeforces.com/problemset/problem/424/B?locale=en
/*

Sorts the cities by distance (and by reverse population at distance draws),
than start adding cities until it reaches the desired population.

*/

#include <bits/stdc++.h>

using namespace std;

struct custom_less {
    inline bool operator() (const pair<int, int>& p1, const pair<int, int>& p2) {
        if (p1.first == p2.first)
			return p1.second > p2.second;
		return p1.first < p2.first;
    }
};

#define population 1000000

int main() {
	int N, s;
	cin >> N >> s;
	vector<pair<int, int>> cities;
	cities.reserve(N);
	for (int i = 0; i < N; ++i) {
		int x, y, l;
		cin >> x >> y >> l;
		cities.push_back(pair<int, int>(x*x + y*y, l));
	}
	sort(cities.begin(), cities.end(), custom_less());
	int distance = 0;
	for (int i = 0; i < N; ++i) {
		if (s >= population) {
			cout << sqrt(distance) << endl;
			break;
		}
		distance = cities[i].first;
		s += cities[i].second;
	}
	if (s < population)
		cout << -1 << endl;

	return 0;
}
