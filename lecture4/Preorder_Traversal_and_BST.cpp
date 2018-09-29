// https://practice.geeksforgeeks.org/problems/preorder-traversal-and-bst/0
/*

The algorithm expects all elements of the array to be different.

The algorithm checks the following property of array A: for each index i let
R(i) be the minimum index greater than i so that A[R(i)] > A[i]. Then the
property is that for each j >= R(i) holds A[j] > A[i].

This property implies (in fact it is equivalent) that is A is the result of
a preorder visit of a BST.
Proof: if the property holds, let prove inductively that a BST can be built.
Consider a generic A[i]. The property says that a subarray beginning right after
A[i] is made of elements lower than A[i], and we use those elements to build the
left subtree of A[i] (thus it respect the BST property). The elements after are
greater, and can go both in the right subtree or in a subtree of an ancestor of
A[i]. Let's split in two cases: if A[i] doesn't have an element greater than it
before, than all elements after it forms its right subtree. This respects the
BST property. In the other case, the elements after A[i] that are lower than any
of its predecessors but greater than him becomes its right subtree (respecting
the BST property for A[i]), and the others will be used to build the right
subtree of one of the predecessors (with this very same rule). From this
construction, for each A[i] the subtree rooted at it respects the BST constraint
(each element in the left subtree is lower than the root that is lower than any
element in the right subtree), thus the whole tree is a BST.

Proof of the other arrow (useless for the problem, but nice): if A is the result
of a preorder visit of a BST, let's check the property for A[i]. After printing
A[i], the preorder goes through the left subtree, thus printing elements lower
than A[i]. After that it starts printing elements of the right subtree that are
greater than A[i] (as required). After that it goes up in the tree to an
ancestor of A[i] (that is greater in a BST), and prints the possible other child
of that ancestor. But if this child exists it is the right child, and A[i] is in
the left subtree, so the whole tree rooted in that node is greater than A[i].

Now the algorithm checks the property in the following way: it keeps a stack and
goes through the array. It pushes any element that is lower than the stack top
until it finds an element x greater. At this point pops from the stack all
elements lower than x, stores in old_min the last element popped in this way,
pushes x on top of the stack and restart. If at any point an element is both
lower than the stack top and old_min, the algorithm returns false (I'll say it
doesn't end meaning it doesn't end properly), else returns true.
Prop 1 - the stack is always sorted (I think its clear).
Prop 2 - an element is popped from the stack by hand of A[R(i)]: an element is
	popped only because a greater element is found after him, an the first found
	is by definition A[R(i)]. It isn't possible that A[R(i)] doesn't pops A[i]
	because the stack is sorted, so any other element in the stack after A[i] is
	lower than A[i] (and thus than A[R(i)]).
Prop 3 - an element in the stack is greater than an element popped from it: this
	is true because an element is popped only if there's an element greater than
	it that is going to be pushed on top of the stack. Thus an element in the
	stack is greater than the elements it popped, that by induction are greater
	than any other element that was in the stack at some point.
Prop 4 - old_min is non decreasing: old_min takes the value of the current stack
	head right before that value is popped from the stack. The previous value of
	old_min was in the stack at some point, thus it was lower than the new one
	(prop 3).
Prop 5 - if the algorithm ends the property holds: the only thing to check is
	that any j >= R(i) respects A[j] > A[i]. The moment when A[i] is popped from
	the stack old_min becomes equals to A[i]. Given its non decreasing property
	(prop 4), each element after that moment should be greater than old_min
	because if it is lower than the stack top the termination assures it, and if
	it is greater than the stack top, this value is greater than old_min because
	old_min was in the stack at some time (prop 3). But A[i] is popped when
	A[R(i)] is processed (prop 2), thus the thesis.

The time complexity is Theta(n) because each element is pushed in the stack
exactly once, so it can be popped at most once. Any other operation is done at
most once for push/pop (while guards check, mostly), thus the bound of N push
plus N pop is a time complexity bound. The space only extra space is costant
plus the stack, that is obviusly O(n), but actually is O(h) where h is the
height of the BST (without proof: the stack contains at any moment the keys of
a descending path from the root to a node).

*/

#include <bits/stdc++.h>

using namespace std;

bool isBSTpreorder(int A[], int N) {
	stack<int> st;
	int old_min = INT_MIN;
	st.push(A[0]);
	int i = 1;
	// cout << "Started" << endl;
	while (i < N) {
		// Descend
		// cout << "Started descend: ";
		while (st.top() > A[i]) {
			if (A[i] < old_min)
				return false; // CHANGE
			st.push(A[i]);
			// cout << A[i] << ' ';
			++i;
		}
		// cout << "\nEnded with " << A[i] << "\nPopped ";
		// Ascend by one
		while(!st.empty() && st.top() < A[i]) {
			old_min = st.top();
			// cout << st.top() << " ";
			st.pop();
		}
		// cout << "\nPushing " << A[i] << " and restarting\n";
		st.push(A[i]);
		++i;
	}
	return true; // CHANGE
}

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;
		int A[N];
		for (int i = 0; i < N; ++i) {
			int a;
			cin >> a;
			A[i] = a;
		}

		cout << (isBSTpreorder(A, N) ? 1 : 0) << endl;
	}
	return 0;
}
