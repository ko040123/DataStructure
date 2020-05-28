/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/
/*
* File: tree.cpp, tree.h, treeDriver.cpp
* implements a binary tree and/or binary search tree(BST).* and
* AVL(Adelson-Velskii and Landis) tree.
*
* A binary search tree BST is a type of binary tree where the nodes
* are arranged in order: for each node, all elements in its left
* subtree are less to to node and all the elements in its right
* subtree are greater than the node. Many operations are the same
* either in a binary tree or in a binary search tree.
*
* - Some functions work for a binary tree and/or for a BST.
* - The code works on the node structure 'tree' that makes up the tree.
* - The algorithm, typically recursive, that iterates over the tree
* - Using a pointer to a pointer as an argument have been avoided.
*   Instead the function is to return a new root node after an
*   insertion or deletion, then it returns the root node as a
*   returned value.
*
* Usage:
*   tree left = new TreeNode(1);
*   tree right = new TreeNode(2);
*   tree root - new TreeNode(3, left, right);
* or
*   tree root = grow(nullptr, 2);
*   root = grow(root, 1);
*   root = grow(root, 3);	// a new node is added
*   root = trim(root, 5);	// if first node is removed,
*                         // the new root is returned
*/

#include <iostream>
#include <cassert>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include "tree.h"
using namespace std;

void treeprint(tree t);        // print the tree on console graphically

// returns the degree of a node, not a tree
int degree(tree t) {
	int d = 0;
	if (t->left != nullptr) d++;
	if (t->right != nullptr) d++;
	return d;
}

// returns the max depth of a tree. It is the same as the number of edges
// along the longest path from the root node down to the farthest leaf node.
// height = -1 for empty tree, 0 for root only tree
int height(tree node) {
	if (empty(node)) return -1;
	int left = height(node->left);
	int right = height(node->right);
	return max(left,right) + 1;
}

// Computes the size of the binary tree dyamically by
// traversing the nodes recursively.
int size(tree node) {
	if (empty(node)) return 0;
	return size(node->left) + size(node->right) + 1;
}

bool empty(tree t) {
	return t == nullptr;
}

int value(tree t) {
	if (!empty(t)) return t->key;
	return 0;
}

// frees all nodes while traversing the tree like postorder
tree clear(tree t) {
	DPRINT(cout << "++++CLEAR++++" << endl;);

	if (empty(t)) return nullptr;

	if(clear(t->left)==nullptr && clear(t->right)==nullptr){
		delete t;
		t = nullptr;
	}
	return t;
}

// does there exist a node with given key?
// search a key in binary search tree(BST) recursively.
bool contains(tree node, int key) {
	if (empty(node)) return false;
	if (key == node->key) return true;
	if (key < node->key) return contains(node->left, key);
	return contains(node->right, key);
}

// does there exist a node with given key?
// search a key in binary tree(BT) recursively.
bool containsBT(tree node, int key) {
	if (empty(node)) return false;
	if(key == node->key) return true;
	return containsBT(node->left, key) || containsBT(node->right, key);
}

// does there exist a key-value pair with given key?
// search a key in binary search tree(BST) iteratively
bool containsIteration(tree node, int key) {
	if (empty(node)) return false;
	DPRINT(cout << ">containsIteration root key=" << node->key << endl;);
	while (node) {
		if (key == node->key) return true;
		node = key < node->key ? node->left : node->right;
	}
	return false;
}

// returns a node with a key given if found in BST, otherwise nullptr.
tree find(tree node, int key) {
	if (empty(node)) return nullptr;

	if (key == node->key) return node;
	if (key < node->key)
		return find(node->left, key);
	return find(node->right, key);
}

// returns a node with a key given if found in BT, otherwise nullptr.
tree findBT(tree root, int key) {
	DPRINT(cout << "++++findBT++++" << endl;);

	if (empty(root)) return nullptr;
	if (root->key == key) return root;
	tree nodeL = findBT(root->left, key);
	tree nodeR = findBT(root->right, key);
	if(nodeL != nullptr) return nodeL;
	if(nodeR != nullptr) return nodeR;
	return nullptr;
}

// returns true if the node x is found and the path from node x to root
// Do not call finaPath() and reverse it.
bool findPathBack(tree root, tree x, vector<int>& path) {
	if (empty(root)) return false;
	if (root->key == x->key) {
		path.push_back(root->key);
		return true;
	}
	if (findPathBack(root->left,x,path) || findPathBack(root->right,x,path)){
		path.push_back(root->key);
		return true;
	}
	return false;
}  // path from node x to root is produced.

// returns true if the node x is found and a vector loaded with a path
// from root to the node x
// Do not call finaPathBack() and reverse it.
bool findPath(tree node, tree x, vector<int>& path) {
	DPRINT(cout << ">findPath size=" << path.size() << endl;);
	if (empty(node)) return false;
	path.push_back(node->key);
	if (node->key == x->key) return true;

	if (!findPath(node->left,x,path) && !findPath(node->right,x,path)){
		path.pop_back();
		DPRINT(cout << "<findPath not found, pop:" << node->key << endl;);
		return false;
	}
	return true;
}

// returns a node with a key given if found in BT, otherwise nullptr.
tree findParent(tree t, int key, tree parent) {
	if (empty(t)) return nullptr;

	if (t->key == key) return parent;

	tree node = findParent(t->left, key, t);
	if (node != nullptr) return node;
	return findParent(t->right, key, t);
}

// inserts a new node with the key in given binary search tree and
// returns the new node such that client use it properly.
tree grow(tree node, int key) {
	DPRINT(cout << ">grow key=" << key << endl;);
	if (node == nullptr) return new TreeNode(key);
	if (key < node->key) node->left = grow(node->left, key);
	else if (key > node->key) node->right = grow(node->right, key);


	// do nothing, the duplicate key is not allowed
	DPRINT(cout << "<grow returns key=" << node->key << endl;);
	return node;    // eventually returns the original root node
}

// inserts a node with the key and returns the root of the binary tree.
// Traversing it in level order, find the first empty node in the tree.
//
// The idea is to do iterative level order traversal of the given tree
// using queue.
// First, push the root to the queue. Then, while the queue is not empty,
// Get the front() node on the queue. Check that the left or right is nullptr.
// If the left child of the node is empty, make new key as left child of
// the node.– breakand return;  else add it to queue to process later
// since it is not nullptr. If the right child is empty, make new key
// as right child of the node.– breakand return; else add it to queue
// to process later since it is not nullptr.  Make sure that you pop
// the queue finished. Do this until you find a node whose either
// left or right is empty.
tree growBT(tree root, int key) {
	DPRINT(cout << ">growBT key=" << key << endl;);
	if(root == nullptr)
		return new TreeNode(key);
	tree node;
	queue<tree> que;
	que.push(root);

	while(!que.empty()){
		node = que.front();
		if(node->left == nullptr){
			node->left = new TreeNode(key);
			break;
		}
		else{
			que.push(node->left);
		}

		if(node->right == nullptr){
			node->right = new TreeNode(key);
			break;
		}
		else{
			que.push(node->right);
		}
		que.pop();
	}
	DPRINT(cout << "<growBT" << endl;);
	return root;    // eventually returns the original root node
}

// creates the complete binary tree from the array in level order traversal.
// When the parent is present at index i, then its two children will be at
// index(2i + 1), and (2i + 2).Thus we can insert leftand right nodes using
// its parent nodes.The first element of the array will be the root of CBT.
tree growBT(tree root, int *arr, int i, int n) {
	DPRINT(cout << ">growBT arr n=" << n << endl;);

	if (i < n) {
		root = new TreeNode(arr[i]);
		root->left = growBT(root->left, arr, 2 * i + 1, n);
		root->right = growBT(root->right, arr, 2 * i + 2, n);
	}
	DPRINT(cout << "<growBT arr" << endl;);
	return root;    // eventually returns the original root node
}

///////////////////////////////////////////////////////////////////
// trim
///////////////////////////////////////////////////////////////////
// removes the node with the key in a tree and returns the new root
tree trim(tree node, int key) {
	if (empty(node)) return node;	 // base case
	DPRINT(cout << ">trim: now we are at: " << node->key << endl;);
	if (key < node->key) // if node to trim is in left subtree.
		node->left = trim(node->left, key);
	else if (key > node->key) // node to trim is in right subtree.
		node->right = trim(node->right, key);
	// found the key: delete the node now
	// node with two childeren: replace it with the successor or predecessor
	else if (node->left && node->right) {//two children
		// compare height(left, right)
		// left: trim predecessor
		if(height(node->left) >= height(node->right)){
			int temp = value(pred(node));
			node->left = trim(node->left, value(pred(node)));
			node->key = temp;
		}
		else{// right: trim successor
			int temp = value(succ(node));
			node->right = trim(node->right, value(succ(node)));
			node->key = temp;
		}

	}
	else if(node->left){//one children(left)
		tree temp = node->left;
		delete node;
		return temp;
	}
	else if(node->right){//one children(right)
		tree temp = node->right;
		delete node;
		return temp;
	}
	else{//no children
		delete node;
		return nullptr;
	}
	DPRINT(if (node != nullptr) cout << "<trim returns: key=" << node->key << endl;);
	DPRINT(if (node == nullptr) cout << "<trim returns: nullptr)\n";);
	return node;
}

// returns a successor of the tree
tree succ(tree node) {
	if (node != nullptr && node->right != nullptr)
		return minimum(node->right);
	return nullptr;
}

// returns a predeccessor of the tree
tree pred(tree node) {
	if (node != nullptr && node->left != nullptr)
		return maximum(node->left);
	return nullptr;
}

// Given a binary search tree, return the min or max key in the tree.
// Don't need to traverse the entire tree.
tree maximum(tree node) {			// returns max node
	if (node->right == nullptr) return node;
	return maximum(node->right);
}

tree minimum(tree node) {			// returns min node
	if (node->left == nullptr) return node;
	return minimum(node->left);
}

// Given a binary tree, return the max key in the tree.
tree maximumBT(tree node) {
	DPRINT(cout << "++++MAXIMUM_BT++++" << endl;);

	if (node == nullptr) return node;
	tree max = node;
	tree x = maximumBT(node->left);
	tree y = maximumBT(node->right);
	if(x == nullptr){}
	else if(x->key > max->key) max = x;
	if(y == nullptr){}
	else if(y->key > max->key) max = y;

	return max;
}

tree minimumBT(tree node) {			// returns min node
	DPRINT(cout << "++++MINIMUM_BT++++" << endl;);

	if (node == nullptr) return node;
	tree min = node;
	tree x = minimumBT(node->left);
	tree y = minimumBT(node->right);
	if(x == nullptr){}
	else if(x->key < min->key) min = x;
	if(y == nullptr){}
	else if(y->key < min->key) min = y;

	return min;
}

// Given a binary tree, its node values in inorder are passed
// back through the argument v which is passed by reference.
void inorder(tree node, vector<int>& v) {
	DPRINT(cout << "++++INORDER1++++" << endl;);

	if (empty(node)) return;
	inorder(node->left, v);
	v.push_back(node->key);
	inorder(node->right, v);
}

// returns a vector that has tree nodes in inorder instead of keys.
void inorder(tree node, vector<tree>& v) {
	DPRINT(cout << "++++INORDER2++++" << endl;);

	if (empty(node)) return;
	inorder(node->left, v);
	v.push_back(node);
	inorder(node->right, v);
}


void inorder(tree node, set<int>& s){
	if(empty(node)) return;
	inorder(node->left,s);
	node->key = *s.begin();
	s.erase(s.begin());
	inorder(node->right,s);
}

// Given a binary tree, its node values in postorder are passed
// back through the argument v which is passed by reference.
void postorder(tree node, vector<int>& v) {
	DPRINT(cout << "++++POSTORDER++++" << endl;);

	if(empty(node)) return;
	DPRINT(cout << ">postorder size=" << v.size() << endl;);
	postorder(node->left, v);
	postorder(node->right, v);
	v.push_back(node->key);
	DPRINT(cout << "<postorder key=" << node->key << endl;);
}

// Given a binary tree, its node values in preorder are passed
// back through the argument v which is passed by reference.
void preorder(tree node, vector<int>& v) {
	DPRINT(cout << "++++PREORDER++++" << endl;);

	if(empty(node)) return;
	DPRINT(cout << ">preorder size=" << v.size() << endl;);
	v.push_back(node->key);
	preorder(node->left, v);
	preorder(node->right, v);
	DPRINT(cout << "<preorder key=" << node->key << endl;);
}

// returns its nodes in level-order passed back through the argument v
// which is passed by reference. This is also called breadth-first
// search(BFS), as the search broadened as much as possible on each
// depth before going to the next depth(level or height).
// Use std::queue to store the nodes during traverse the tree.
// Using queue requires extra space to save nodes in the queue.
// It is proportional to the maximum number of nodes at given depth.
// This can be as much as one half of the total number nodes. O(n)
void levelorder(tree root, vector<int>& vec) {
	DPRINT(cout << "++++LEVEL_ORDER++++" << endl;);
	tree node;
	queue<tree> que;
	if (empty(root)) return;
	que.push(root);

	while(!que.empty()){
		node = que.front();
		vec.push_back(node->key);
		if(node->left != nullptr)
			que.push(node->left);
		if(node->right != nullptr)
			que.push(node->right);
		que.pop();
	}
	DPRINT(cout << "<levelorder size=" << vec.size() << endl;);
}

// returns LCA(Least Common Ancestor) of a binary tree [BT]
tree LCA_BT(tree root, tree p, tree q) {  // recursive solution
	DPRINT(cout << ">LCA_BT" << endl;);
	// base case 1: no p or q found
	if (root == nullptr) return nullptr;
	if (root == p || root == q) return root;
	//recursive case
	tree nodeL = LCA_BT(root->left,p,q);
	tree nodeR = LCA_BT(root->right,p,q);
	//trace back
	if(nodeL == nullptr && nodeR == nullptr) return nullptr;
	else if(nodeL == nullptr) return nodeR;
	else if(nodeR == nullptr) return nodeL;

	return root;
}

// returns LCA(Least Common Ancestor) of a binary tree [BT]
int LCA_BTiteration(tree root, tree p, tree q) {
	DPRINT(cout << ">LCA_BTiteration" << endl;);
	vector<int> vec1, vec2;
	int temp = 0;
	if(findPathBack(root, p, vec1) && findPathBack(root, q, vec2)){
		while(!vec1.empty() && !vec2.empty()){
			if(vec1.back() == vec2.back()){
				temp = vec1.back();
				vec1.pop_back();
				vec2.pop_back();
			}
			else{break;}
		}
		return temp;
	}
	return 0;
}

// returns LCA(Least Common Ancestor) of a binary search tree
// The lowest common ancestor is defined between two nodes pand q as the
// lowest node in T that has both pand q as descendants(where we allow a
// node to be a descendant of itself). Given BST, two descedents p and q,
// root = [6, 2, 8, 0, 4, 7, 9, null, null, 3, 5], p=2, q=8, then output=6
// root = [6, 2, 8, 0, 4, 7, 9, null, null, 3, 5], p=2, q=4, then output=2
// since a node can be a descendent of itself according to the LCA definition.
// Notice that both p and q exist and are unique in a given tree by definition.
tree LCA(tree root, tree p, tree q) {  // recursive solution
	DPRINT(cout << ">LCA" << endl;);

	// base case 1: no p or q found
	if (root == nullptr) return nullptr;
	if (root == p || root == q) return root;
	// recursive case
	// p,q both on left subtree
	if(p->key < root->key && q->key < root->key)
		return LCA(root->left, p, q);
	// p,q both on right subtree
	else if(p->key > root->key && q->key > root->key)
		return LCA(root->right, p, q);
	DPRINT(cout << "<LCA" << endl;);
	return root;
}

int LCAiteration(tree root, tree p, tree q) {  // iteration solution
	DPRINT(cout << ">LCAiteration " << endl;);
	while(root != nullptr){
		if(p->key > root->key && q->key > root->key)
			root = root -> right;
		else if(p->key < root->key && q->key < root->key)
			root = root ->left;
		else
			break;
	}
		DPRINT(cout << "<LCAiteration"  << endl;);
	return root->key;
}

// does this binary tree satisfy symmetric order?
// is the tree rooted at x a BST with all keys between min and max?
// Another solution: Do an inorder traversal of the tree and store
// the node values in a container. If it is in sorted order,
// its a valid BST otherwise not.
bool isBST(tree x, int min, int max) {
	if (empty(x)) return true;
	DPRINT(cout << ">isBST key=" << x->key << "\t min=" << min << " max=" << max << endl;);
	bool result = true;
	vector<int> v;
	inorder(x,v);
	for(int i = 1; i < v.size(); i++){
		if(v[i-1] > v[i]) result = false;
	}

	DPRINT(cout << "<isBST key=" << x->key << "\t min=" << min << " max=" << max << " false\n";);
	return result;
}

// returns true if the tree is a binary search tree, otherwise false.
bool isBST(tree root) {
	if (empty(root)) return true;
	bool result = isBST(root, INT_MIN, INT_MAX);
	DPRINT(cout << "<isBST result=" << result << endl;);
	return result;
}

// a helper function to get keys in BT and save them in a set.
void get_keys(tree root, set<int> &keys) {
	DPRINT(cout << " >get_keys" << endl;);
	if (root == nullptr) return;
	keys.insert(root->key);
	DPRINT(cout << " get(" << root->key << ") " << endl;);
	get_keys(root->left, keys);
	get_keys(root->right, keys);
	DPRINT(cout << " ><get_keys" << endl;);
}

//////////////////////////////////////////////////////////////////
// define helper functions here to get/set keys for BTtoBST()

// returns a BST converted from a binary tree in-place.
// Use a vector or set in STL. Do not use an array to store keys.
void BTtoBST(tree root) {
	DPRINT(cout << ">BTtoBST" << endl;);

	vector<int> v;
	set<int> s;
	inorder(root,v);
	for(int i = 0; i < v.size(); i++)	s.insert(v[i]);

	inorder(root,s);
	DPRINT(cout << ">BTtoBST" << endl;);
}

///////////////// stress test - insert, trim ////////////////////

// returns an extended random number of which the range is from 0
// to (RAND_MAX + 1)^2 - 1. // We do this since rand() returns too
// small range [0..RAND_MAX) where RAND_MAX is usually defined as
// 32767 in cstdlib. Refer to the following link for details
// https://stackoverflow.com/questions/9775313/extend-rand-max-range
unsigned long rand_extended(int range) {
	if (range < RAND_MAX) return rand();
	return rand() * RAND_MAX + rand();
}

// shuffles an int array contents
void shuffle(int* arr, int N) {
	DPRINT(cout << ">shuffle N=" << N << endl;);
	if (N <= 1) return;
	DPRINT(srand(0));    // for the same sequence of rand() for debugging
	for (int i = 0; i < N; i++) {
		int x = rand_extended(N) % (N - 1);
		int t = arr[i];
		arr[i] = arr[x];
		arr[x] = t;
	}
	DPRINT(cout << "<shuffled" << endl;);
}

// returns an int array that has randomly mixed numbers
// between start to start + N
void randomN(int* arr, int N, int start) {
	DPRINT(cout << ">random N=" << N << endl;);
	for (int i = 0; i < N; i++)
		arr[i] = start + i;
	shuffle(arr, N);

#ifdef DEBUG
	cout << "randomN: ";
	for (int i = 0; i < N; i++) cout << arr[i] << " ";
	cout << "\n";
	cout << "<random" << endl;
#endif
}

// inserts N numbers of keys in the tree(AVL or BST), based
// on the current menu status.
// If it is empty, the key values to add ranges from 0 to N-1.
// If it is not empty, it ranges from (max+1) to (max+1 + N).
// For AVL tree, use BST grow() and reconstruct() once at root.
tree growN(tree root, int N, bool AVLtree) {
	DPRINT(cout << ">growN N=" << N << endl;);
	int start = empty(root) ? 0 : value(maximum(root)) + 1;

	int* arr = new (nothrow) int[N];
	assert(arr != nullptr);
	randomN(arr, N, start);

	#if 1
	for (int i = 0; i < N; i++) root = grow(root, arr[i]);
	////////////// use this line with AVL code completion /////////
	if (AVLtree) root = reconstruct(root);

	#else
	if(AVLtree) for(int i = 0; i < N; i++) root = growAVL(root,arr[i]);
	else for(int i = 0; i < N; i++) root = grow(root,arr[i]);
	#endif

	delete[] arr;
	DPRINT(cout << "<growN size=" << size(root) << endl;);
	return root;
}

// removes randomly N numbers of nodes in the tree(AVL or BST).
// It gets N node keys from the tree, trim one by one randomly.
// For AVL tree, use BST trim() and reconstruct() once at root.
tree trimN(tree root, int N, bool AVLtree) {
	DPRINT(cout << ">trimN N=" << N << endl;);
	vector<int> v;
	inorder(root, v);
	if(v.size() < N) N = v.size(); cout << endl;
	shuffle(v.data(),v.size());
	for(int i = 0; i < N; i++){
		root = trim(root,v[i]);
	}

	////////////// use this line with AVL code completion /////////
	if (AVLtree) root = reconstruct(root);

	DPRINT(cout << "<trimN size=" << size(root) << endl;);
	return root;
}

////////////////////////// AVL Tree ///////////////////////////////
bool balanced(tree node) {
	int factor = balanceFactor(node);
	return (factor >= -1 && factor <= 1) ? true : false;
}

// returns the balance factor or (height of left - height of right)
int balanceFactor(tree node) {
	DPRINT(cout << " bf" << endl;);
	if (empty(node)) return 0;
	int left = height(node->left);
	int right = height(node->right);
	return left - right;
}

// returns true if the tree is AVL tree.
// this is a helper function for isAVL().
bool _isAVL(tree root) {
	if (!balanced(root)) return false;
	if (root->left != nullptr && !_isAVL(root->left))  return false;
	if (root->right != nullptr && !_isAVL(root->right)) return false;
	return true;
}
bool isAVL(tree root) {
	if (empty(root)) return true;
	if (!isBST(root)) return false;
	return _isAVL(root);
}

tree rotateLL(tree node) {
	DPRINT(cout << "\t[LL]case at " << node->key << endl;);
	cout << "\t[LL]case at " << node->key << endl;
	tree child = node->left;
	node->left = child->right;
	child->right = node;
	return child;
}

tree rotateRR(tree node) {
	DPRINT(cout << "\t[RR]case at " << node->key << endl;);
	cout << "\t[RR]case at " << node->key << endl;
	tree child = node->right;
	node->right = child->left;
	child->left = node;
	return child;
}

tree rotateLR(tree node) {
	DPRINT(cout << "\t[LR]case at " << node->key << endl;);
	cout << "\t[LR]case at " << node->key << endl;
	tree child = node->left;
	node->left = rotateRR(child);
	return rotateLL(node);
}

tree rotateRL(tree node) {
	DPRINT(cout << "\t[RL]case at " << node->key << endl;);
	cout << "\t[RL]case at " << node->key << endl;
	tree child = node->right;
	node->right = rotateLL(child);
	return rotateRR(node);
}

// rebalnces at the node only, not recursively, and
// returns the node that may be different from the input node
tree rebalance(tree node) {
	DPRINT(cout << ">rebalance at:" << node->key << endl;);
	if(node == nullptr) return nullptr;
	int bf= balanceFactor(node);

	if(bf >= 2){
		if(balanceFactor(node->left) >= 1) //single rotation
			node = rotateLL(node);
		else
			node = rotateLR(node);

	}

	else if(bf <= -2){
		if(balanceFactor(node->right) <= -1) //single rotation
			node = rotateRR(node);
		else
			node = rotateRL(node);
	}

	DPRINT(cout << "<no rebalance" << endl;);
	return node;
}

// rebuilds an AVL/BST tree with a list of keys sorted.
// v – an array of keys sorted, n – the array size
tree buildAVL(int* v, int n) {  // recreation method
	if (n <= 0) return nullptr;
	int mid = n / 2;

	DPRINT(cout << ">buildAVL v[0]=" << v[0] << " n=" << n << " mid=" << n / 2 << endl;);

	tree node = new TreeNode(v[mid]);

	node->left = buildAVL(v,mid);
	node->right = buildAVL(v+mid+1,n-(mid+1));

	return node;
}

// rebuilds an AVL/BST tree using a list of nodes sorted, no memory allocations
// v – an array of nodes sorted, n – the array size
tree buildAVL(tree* v, int n) {  // recycling method
	if (n <= 0) return nullptr;
	tree node;
	int mid = n / 2;

	if(n == 2){
		node = v[mid];
		node->left = buildAVL(v,mid);
		node->right = nullptr;
		return node;
	}
	else if(n == 1){
		node = v[mid];
		node->left = nullptr;
		node->right = nullptr;
		return node;
	}
	else{
		node = v[mid];
		node->left = buildAVL(v,mid);
		node->right = buildAVL(v+mid+1,n-(mid+1));
	}
	DPRINT(cout << "<buildAVL" << n << endl;);
	return node;
}

// reconstructs a new AVL tree in O(n), Actually it is O(n) + O(n).
// Use the recreation method if the size is less than or equal to 10
// Use the recycling method if the size is greater than 10.
// recreation method: creates all nodes again from keys
// recycling method: reuses all the nodes, no memory allocation needed
tree reconstruct(tree root) {
	DPRINT(cout << ">reconstruct " << endl;);
	if (empty(root)) return nullptr;

	if (size(root) > 10) {// recycling method
		vector<tree> vt;
		inorder(root,vt);    // use new inorder() that returns nodes sorted
	          							// O(n), v.data() - the array of nodes(tree) sorted
		root = buildAVL(vt.data(), (int)vt.size()); // O(n)
	}
	else {                    // recreation method
		vector<int> vi;         // use inorder() that returns keys sorted
	  inorder(root,vi);        // O(n), v.data() - the array of keys(int) sorted
		clear(root);                      // clear root
		root = buildAVL(vi.data(), (int)vi.size()); // O(n)
	}
	DPRINT(cout << "<reconstruct " << endl;);
	return root;
}

// inserts a key into the AVL tree and rebalance it.
tree growAVL(tree node, int key) {//O(logn)
	DPRINT(cout << ">growAVL key=" << key << endl;);
	if (empty(node)) return new TreeNode(key);

	if(key < node->key)
		node->left = growAVL(node->left, key);
	if(key > node->key)
		node->right = growAVL(node->right,key);

	return rebalance(node);      // O(1)
}

// removes a node with key in the AVL tree and rebalance it.
tree trimAVL(tree node, int key) {
	DPRINT(cout << ">trimAVL key=" << key << " at " << node->key << endl;);

	// step 1 - BST trim as usual
	if (empty(node)) return node;	// base case

	// then node to trim must be in left subtree.
	if (key < node->key)
		node->left = trimAVL(node->left, key);
	// then node to trim must be in right subtree.
	else if (key > node->key)
		node->right = trimAVL(node->right, key);
	// node with two childeren: replace it with the successor or predecessor
	else if (node->left && node->right) {
		if(height(node->left) >= height(node->right)){
			int temp = value(pred(node));
			node->left = trimAVL(node->left, value(pred(node)));
			node->key = temp;
		}
		else{
			int temp = value(succ(node));
			node->right = trimAVL(node->left, value(succ(node)));
			node->key = temp;
		}
	}
	else if(node->left){
		tree temp = node->left;
		delete node;
		return temp;
	}
	else if(node->right){
		tree temp = node->right;
		delete node;
		return temp;
	}
	else{
		delete node;
		return nullptr;
	}

	if (node == nullptr) return node;   // redundant code, but useful

	// step 2 - get rebalanced at this node
	DPRINT(if (node != nullptr)
		cout << "<trimAVL key=" << key << " is done, now rebalance at " << node->key << endl;);
	return rebalance(node);
}


///////////////////// helper functions /////////////////////////////////
// prints elements present in a vector in a line, show_n items per line
void show_vector(vector<int> vec, int show_n) {
	size_t size = vec.size();
	if (size < show_n)
		for (auto i : vec) cout << i << " ";
	else {
		for (int i = 0; i < show_n / 2; ++i)
			cout << vec[i] << " ";
		cout << "... ";
		for (size_t i = size - show_n / 2; i < size; ++i)
			cout << vec[i] << " ";
	}
}
