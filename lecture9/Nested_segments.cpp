// http://codeforces.com/problemset/problem/652/D?locale=en
/*

Algorithm described at lesson: sorts the segments by end point, then examine
them asking the Fenwick tree how many segments begin before the current
segment's starting point. Then updates the Fenwick with that starting point.
The answer for a segment is actually the number of processed segments minus
those which starts before the current segment.

Space complexity is Theta(n). Time complexity is Theta(N * log N), because of
both sorting and Theta(N) operation on the Fenwick tree.

*/

#include <bits/stdc++.h>

using namespace std;

#define lsb(x) (x & -x)
#define lli long long int

void update(vector<int> &ftree, lli i, int val) {
	//+lsb
	while (i < ftree.size()) {
		ftree[i] += val;
		i += lsb(i);
	}
}

unsigned int query(const vector<int> &ftree, long long int i) {
	//-lsb
	int sum = 0;
	while (i != 0) {
		sum += ftree[i];
		i -= lsb(i);
	}
	return sum;
}

int main() {
	int N;
	cin >> N;
	vector<pair<lli, lli>> segments;
	vector<unsigned lli> indexes;
	vector<pair<lli, int>> ends;
	segments.reserve(N);
	indexes.resize(N);
	ends.reserve(2 * N);
	for (int i = 0; i < N; ++i) {
		long long int l, r;
		cin >> l >> r;
		segments.push_back(pair<lli, lli>(r, l));
		ends.push_back(pair<lli, int>(l, i));
		ends.push_back(pair<lli, int>(r, i));
		indexes[i] = i;
	}
	sort(ends.begin(), ends.end());
	// Makes ends of the segments contiguos, from 0 to 2 * N - 1
	for (int i = 0; i < ends.size(); ++i) {
		if (segments[ends[i].second].first == ends[i].first)
			segments[ends[i].second].first = i + 1;
		else
			segments[ends[i].second].second = i + 1;
	}

	sort(indexes.begin(), indexes.end(), [&segments](size_t i1, size_t i2) { return segments[i1].first < segments[i2].first; });

	vector<int> ftree(2 * N + 1, 0);
	unsigned int results[N];
	for (int i = 0; i < N; ++i) {
		results[indexes[i]] = i - query(ftree, segments[indexes[i]].second);
		update(ftree, segments[indexes[i]].second, 1);
	}
	for (int i = 0; i < N; ++i) {
		cout << results[i] << "\n";
	}
	return 0;
}
