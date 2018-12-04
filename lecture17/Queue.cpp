// https://codeforces.com/problemset/problem/141/C?locale=en
/*

Let h[i] be the height of the i-th person, and a[i] be the number of person i
(# of higher people before i). Let A_i = { k < i | h[k] > h[i] },
then a[i] = #A_i.

OSS1: given i and j that counts for a[i] (that is, j < i and h[j] > h[i]),
a[j] < a[i]. This because for any k in A_j it holds k < j < i and
h[k] > h[j] > h[i], thus k is in A_i, and j is in A_i but not in A_j (so the
strong inequality).
OSS2: if a[j] == a[i] and j < i, then h[j] < h[i]. Otherwise we would have
(h[i] != h[j]) a[j] < a[i] == a[j] (by OSS1), absurd. Thus groups of people with
the same a[i] have sorted height.

The algorithm proceeds as follows: takes all elements with minimum a[i] = V not
yet placed and put them in the queue, starting at position V and going right,
skipping positions already occupied. It also assigns heights in ascending order
starting from the value that follows the maximum already in the queue. Repeats
this for any V.

The algorithm ensures that if j is before i in the queue than a[j] <= a[i], and
that a[j] == a[i] iff h[j] < h[i], so a[i] is the number of people j before i in
the queue with a[j] < a[i].
Let's suppose this algorithm doesn't find a correct solution. This means that in
the queue there is a person (with index i in array a) such that there aren't
a[i] people with a[j] < a[i] in the array of people. But from OSS1 this means
there's no solution at all.
Viceversa, if this algorithm ends it find a correct solution because it puts
exactly a[i] people with a[j] < a[i] before people i.

Space complexity is Theta(N) to store the results array. Time complexity is
O(N ^ 2): the main while is executed at most N times, and inside it there are
two cycles, each which can perform at most O(N) operations.
This bound is strict: in reversed order of a[i] we find N / 2 elements, than
alternated 1 and 3 elements. This means that on alternated iteration the for
traverses at least N / 2 elements, and the iteration are N / 4, so a total of
Omega(N ^ 2).

OSS: it's possible to lower this bound with a data structure to get the next
free slot faster. For instance, a fenwick tree with 0 in occupied slots and 1
otherwise would allow a binary search (the first empty slot after i is the
first index j that has a value higher by one of that of i). This yield a time
complexity of O(N * log^2(N)).

I actually tested two slightly different solutions for this problem. The only
difference is that in one case result is long 2 * N, there is no check during
the main cycle (2 * N) is enough to guarantee that freeIdx will never indexes
result out of bounds) and after that a single for checks for empty slots up to
N. This solution is obviously better in space, but is slightly slower when there
is a solution.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	pair<int, string> people[N];
	for (int i = 0; i < N; ++i) {
		string name;
		int a;
		cin >> name >> a;
		people[i] = pair<int, string>(a, name);
	}
	sort(people, people + N);
	// Index in the array a[i], starts from highest values
	int i = N - 1;
	// Height to be assigned
	int h = 1;
	// Result
	vector<pair<string, int>> result(N, pair<string, int>("", 0));
	//~ vector<pair<string, int>> result(2 * N, pair<string, int>("", 0));
	while (i >= 0) {
		// Searches the next change of values
		int V = people[i].first;
		int j = i;
		while (people[j].first == V && j >= 0) --j;
		// Insert people with a[k] = V
		// Index of the first space in result in which a new person may be put,
		// will be moved while adding people
		int freeIdx = V;
		for (int k = j + 1; k < i + 1; ++k) {
			while (result[freeIdx].second != 0 && freeIdx < N) ++freeIdx;
			//~ while (result[freeIdx].second != 0) ++freeIdx;
			// The solution found at the end of the algorithm is correct iff
			// there are no empty slots up to N. But, given that there are
			// exactly N elements, this is equivalent to never put an element
			// after N
			if (freeIdx == N) {
				cout << -1 << endl;
				return 0;
			}
			result[freeIdx] = pair<string, int>(people[k].second, h);
			++h;
		}
		i = j;
	}

	//~ // This is a solution iff there are no empty slots up to N
	//~ for (int i = 0; i < N; ++i) {
	//~ 	if (result[i].second == 0) {
	//~ 		cout << -1 << endl;
	//~ 		return 0;
	//~ 	}
	//~ }
	for (int i = 0; i < N; ++i) {
		cout << result[i].first << " " << result[i].second << "\n";
	}

	return 0;
}
