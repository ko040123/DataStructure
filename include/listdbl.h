/**
 * File: listdbl.cpp, listdbl.h
 *       implements a doubly linked list with sentinel nodes
 *       and test it interactively
 *
 * 04/13/16:	Created by idebtor@gmail.com
 * 02/10/19:	C++ conversion, doubly linked list
 * 04/20/20:	sort and merge added
 *
 * 1. This implements a doubly linked list with two sentinel nodes which
 *    provide with benifits of coding consistency and easy maintenance.
 * 2. It does not implment C++ iterator (which is deprecated), but simulated
 *    most of memeber functions defined in std::List.
 */
#ifndef LISTDBL_H
#define LISTDBL_H

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

#include "sort.h"

struct Node{
	int		data;
	Node*	prev;
	Node*	next;
	// constructor instantiates a node, sets data and next
	Node(const int d = 0, Node* p = nullptr, Node* x = nullptr) {
		data = d; 	prev = p;	next = x;
	}
	/* initializer list ///////////////////////////////////
	Node() : data(0), prev(nullptr), next(nullptr) {};
	Node(int i) : data(i), prev(nullptr), next(nullptr) {};
	Node(int i, Node* n): data(i), prev(p), next(n) {};
	*//////////////////////////////////////////////////////
	~Node() {}
};

struct List{
	Node* head;	// sentinel node
	Node* tail;	// sentinel node
	int   size; // size of list, optional
	// constructor instantiates a list, sets doubly-linked head and tail
	List() {
		head = new Node{};    tail = new Node{};
		head->next = tail;    tail->prev = head;
		size = 0;
	}
	~List() {}
};
using pNode = Node *;
using pList = List *;

///////////////////// basic functions //////////////////////////////
pNode begin(pList p);			// returns the first node, not header
pNode end(pList p);				// returns the tail sentinel node
pNode last(pList p);			// returns the last node
void clear(pList p);			// frees nodes, not list
bool empty(pList p);			// true if empty, false if no empty
int size(pList p);				// returns the number of nodes

// returns the first node of the second half, used in show() and shuffle()
pNode half(pList p);            // returns the node in the middle

// returns the first node with value found or the tail node, end(p)
pNode find(pList p, int value);

///////////////////// insert and erase //////////////////////////////
// inserts a new node with value at the position of the node x. O(1)
void insert(pNode x, int value);

// removes from the list a single node x given. O(1)
void erase(pNode x);			// assumes that x is a valid node
void erase(pList p, pNode x);	// checks if x is either tail or head
/////////////////////////////////////////////////////////////////////

///////////////////////// push //////////////////////////////////////
// inserts a new node with val at the beginning of the list. O(1)
void push_front(pList p, int value);

// adds a new node with value at the end of the list, O(1)
void push_back(pList p, int value);

// inserts a new node with value at the position of the node with x.
void push(pList, int value, int x);

// adds N number of new nodes at the end of the list. O(n)
// If the value is not given, randomly generated values are used in 
// the range of [0..(N + size(p))]. Otherwise, simply insert the same 
// value for N times.
void push_backN(pList p, int N);
void push_backN(pList p, int N, int value);

////////////////////////// pop ///////////////////////////////////
void pop_front(pList p);          // pops the first node O(1)
void pop_back(pList p);           // pops the last node O(1)
void pop(pList p, int value);     // pops 1st node with value found
void pop_all(pList p, int val);   // pops all nodes with value O(n)

// pops N nodes from the end, all nodes if N = 0, O(n).
void pop_backN(pList p, int N = 0);

/////////////////////// unique, reverse, shuffle /////////////////
// removes extra nodes that have duplicate consecutive values. O(n)
void unique(pList p);

// reverses the order of the nodes in O(n)
void reverse(pList p);  

// returns shuffled list in O(n), ex)1234567890 returns 6172839405.
void shuffle(pList p);

///////////////////////// sort //////////////////////////////////
// returns the node of which value is larger or smaller than x found
pNode more(pList p, int x);
pNode less(pList p, int x);

// returns true if sorted either by either ascending or descending
bool sorted(pList p);
bool sorted(pList p, int (*comp)(int a, int b));

// inserts a node with value in sorted in the "sorted" list, O(n)
void push_sorted(pList p, int value); 

// inserts N number of nodes in sorted in the sorted list. O(n^2)
void push_sortedN(pList p, int N);

// inserts N number of nodes in sorted in the sorted list. O(nlogn)
void push_sortedNlog(pList p, int N);

// algorithm specific sort functions, refer to listsort.cpp for detail.
void bubbleSort(pList p, int(*comp)(int, int) = ascending);
void insertionSort(pList p, int(*comp)(int, int) = ascending);
void selectionSort(pList p, int(*comp)(int, int) = ascending);
void quickSort(pList p, int(*comp)(int, int) = ascending);
void quickSort(int* a, int n, int(*comp)(int, int) = ascending);

///////////////////////// show ///////////////////////////////////////
// if all is true, show all nodes; otherwise, show_n * 2 nodes at front & back. 
void show(pList p, bool all=true, int show_n=12);  // 12: a default magic number
#endif // LISTDBL_H
