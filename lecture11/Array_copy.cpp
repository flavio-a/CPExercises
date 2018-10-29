// https://practice.geeksforgeeks.org/problems/missing-number-in-array/0
// TODO
/*

The array B is never modified, and update operations are stored in a segment
tree over the array B. Each node of the tree keeps information on the last query
that completely contains it (and a flag to remember that the information is
valid) and the actual informations. Updates are updates on the segment tree,
with the difference that a valid information is propagated to its sons before
the update. Queries are done exploring the segment tree.

Space complexity is Theta(n) for the segment tree. Time complexity is O(m log n)
because each operation (both copy and access) is an operation on the segment
tree.

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {

	}
	return 0;
}
