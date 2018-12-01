// http://codeforces.com/problemset/problem/603/A?locale=en
/*

Greedy algorithm: the flipped array correspond to a pair of flips that affects
from a position onward, and maximize the value flipping an array is equivalent
to maximaze the value with those two filps. I'll say say that a filp is at i if
it changes all and only values after position i.

Let's prove that a single filp may add at most one to the length of an alternate
subsequence. Let's consider a flip at i, and let S0 be the maximal subsequence
ending with a 0 in the subarray up to i (excluded), S1 the one starting with
a 0 in the subarray from i onward and S2 like S1 but starting with a 1. Before
the flip the maximal subsequence that jumps from a 0 to a 1 between i is the
concatenation of S0 + S2, while the one after the flip is S0 + S1. But S1 and S2
can't differ by more than 1: if not, WLOG S2 > S1, we can take S1 as the
subsequence of S2 removing the first character and obtaining a longer
subsequence. Likewise, the maximal subsequence that jumps from a 1 to a 0
between i respects the same bound, thus the claim is proved.

So the two flips required are any pair of flips that both increases the length
by one. This is easily achieved flipping between a pair of consecutive equal
symbols.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	string s;
	cin >> s;
	char last = s[0];
	unsigned char flips = 2;
	unsigned int result = 1;
	for (int i = 1; i < s.length(); ++i) {
		if (s[i] != last) {
			++result;
			last = s[i];
		}
		else if (flips > 0) {
			--flips;
			++result;
		}
	}
	// If flips == 1 the flipped subarray arrives at the end
	// If flips == 2 the flipped subbarray is the whole array
	cout << result << endl;
	return 0;
}
