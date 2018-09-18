// https://practice.geeksforgeeks.org/problems/next-larger-element/0
/*

Explanation of the algorithm:
like the maximum of subarrays, I keep a deque, inserting elements from the head
and removing any element (from the head) until the first greater than the new
element. This value is the first greater than the element inserted at its left.
Let's prove this: the deque is sorted and contains all and only right leaders
(proved for maximum of subarrays) of a prefix. Let's add an element x and do
the stuff. Now the second element of the deck is greater than x, and is to its
left. Any other element in the array between those two is lower than the
second element in the deque (because it's a right leader) and can't be greater
than x, otherwise it wouldn't have been removed when x was inserted. Thus the
second element is the first element to the left of x greater than x.

Just building the deque reversed creates the first element greater to its right.

Time complexity is Theta(n) for the very same reason used for maximum of
subarrays. Space complexity is O(n) but can go down to costant depending on the
input.

*/
#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int main(){
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// Reading input
		int N;
		cin >> N;
		int A[N];
		for (int i = 0; i < N; ++i){
			int x;
			cin >> x;
			A[i] = x;
		}

		// Filling array of results, using the deque
		int R[N];
		deque<int> d;
		for (int i = N - 1; i >= 0; --i) {
			while(!d.empty() && d.front() < A[i]) {
				d.pop_front();
			}
			R[i] = d.empty() ? -1 : d.front();
			d.push_front(A[i]);
		}

		cout << R[0];
		for (int i = 1; i < N; ++i)
			cout << ' ' << R[i];
		cout << '\n';
	}

	return 0;
}
