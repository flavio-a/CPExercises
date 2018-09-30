// https://practice.geeksforgeeks.org/problems/maximum-path-sum/1
/*

Recursively, the maximum possible sum of a tree may be the maximum of one of its
subtrees, or the path from the most distant leaf of one to the most distant leaf
of the other. Likewise, the most distant leaf of a tree is the most distant leaf
of one of its subtrees (the most distant of the two).
The time complexity is Theta(N) where N is the number of leaf because each leaf
is explored exactly once. The space complexity is Theta(h) where h is the height
of the tree because the call stack is size of height of the node being explored.

*/

#include<bits/stdc++.h>
using namespace std;
struct Node{
	int data;
	Node *left, *right;
};
Node *newNode(int data)
{
    Node *node = new Node;
    node->data = data;
    node->left = node->right = NULL;
    return (node);
}
int maxPathSum(struct Node *root);
void insert(Node *root, int a1,int a2, char lr){
	if(root==NULL)
		return ;
	if(root->data==a1){
		switch(lr){
			case 'L':root->left=newNode(a2);
					break;
			case 'R':root->right=newNode(a2);
					break;
		}
	}
	insert(root->left,a1,a2,lr);
	insert(root->right,a1,a2,lr);
}
void inorder(Node *root){
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right)
;}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		Node *root=NULL;
		while(n--){
			int a1,a2;
			char lr;
			cin>>a1>>a2>>lr;
			if(root==NULL){
				root=newNode(a1);
				switch(lr){
					case 'L':root->left=newNode(a2);
							break;
					case 'R':root->right=newNode(a2);
							break;
				}
			}
			else
				insert(root,a1,a2,lr);
		}
		//inorder(root);
		//cout<<endl;
		cout<<maxPathSum(root)<<endl;
	}
}


/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/*Complete the function below
Node is as follows
struct Node{
	int data;
	Node *left, *right;
};
*/

struct pathLeaf {
	int path;
	int leaf;

	pathLeaf(int a, int b) {
		path = a;
		leaf = b;
	};
};

pathLeaf calcPathLeaf(struct Node* root) {
	if (root == NULL)
		return pathLeaf(0, 0);
	auto pl1 = calcPathLeaf(root->left);
	auto pl2 = calcPathLeaf(root->right);
	int path = max(pl1.path, pl2.path);
	if (pl1.leaf != 0 && pl2.leaf != 0)
		path = max(path, pl1.leaf + pl2.leaf + root->data);
	int leaf = root->data + max(pl1.leaf, pl2.leaf);
	return pathLeaf(path, leaf);
}

int maxPathSum(struct Node *root) {
	return calcPathLeaf(root).path;
}
