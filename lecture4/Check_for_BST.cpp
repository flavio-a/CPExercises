// https://practice.geeksforgeeks.org/problems/check-for-bst/1
/*

The function checkBST computes minimum, maximum and BSTness of a tree. Those
three values are used to recursively determine whether a tree is a BST in the
obvious way.

*/


#include <bits/stdc++.h>
using namespace std;
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};
/* Returns true if the given tree is a binary search tree
 (efficient version). */
bool isBST(struct Node* node);
int isBSTUtil(struct Node* node, int min, int max);
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct Node* newNode(int data)
{
  struct Node* node = (struct Node*)
                       malloc(sizeof(struct Node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return(node);
}
/* Driver program to test size function*/
int main()
{
  int t;
  struct Node *child;
  scanf("%d", &t);
  while (t--)
  {
     map<int, Node*> m;
     int n;
     scanf("%d",&n);
     struct Node *root = NULL;
     while (n--)
     {
        Node *parent;
        char lr;
        int n1, n2;
        scanf("%d %d %c", &n1, &n2, &lr);
      //  cout << n1 << " " << n2 << " " << (char)lr << endl;
        if (m.find(n1) == m.end())
        {
           parent = newNode(n1);
           m[n1] = parent;
           if (root == NULL)
             root = parent;
        }
        else
           parent = m[n1];
        child = newNode(n2);
        if (lr == 'L')
          parent->left = child;
        else
          parent->right = child;
        m[n2]  = child;
     }
     cout << isBST(root) << endl;
  }
  return 0;
}


/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/* A binary tree node has data, pointer to left child
   and a pointer to right child
struct Node {
    int data;
    Node* left, * right;
}; */
/* Should return true if tree represented by root is BST.
   For example, return  value should be 1 for following tree.
         20
     /      \
   10       30
  and return value should be 0 for following tree.
         10
     /      \
   20       30 */
// isBST, min, max

struct checkResult {
	bool isBST;
	int min, max;

	checkResult(bool a, int b, int c) {
		isBST = a;
		min = b;
		max = c;
	}
};

checkResult checkBST(Node* root) {
	if (root == NULL)
		return checkResult(true, INT_MAX, INT_MIN);
	auto pleft = checkBST(root->left);
	auto pright = checkBST(root->right);
	if (!pleft.isBST || !pright.isBST)
		return checkResult(false, 0, 0);
	if (root->data >= pleft.max && root->data <= pright.min)
		return checkResult(
				true,
				root->left == NULL ? root->data : pleft.min,
				root->right == NULL ? root->data : pright.max
			);
	return checkResult(false, 0, 0);
}

bool isBST(Node* root) {
    return checkBST(root).isBST;
}
