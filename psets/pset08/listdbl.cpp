/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/
/*
* 04/20/20: show, show_n added
*
* 1. This implements a doubly linked list with two sentinel nodes which
*    provide with benifits of coding consistency and easy maintenance.
* 2. It does not implment C++ iterator (which is deprecated), but simulated
*    most of memeber functions defined in std::List.
*
* The following command removes some invisible bad character in the code file.
*    iconv -f utf-8 -t utf-8 -c file.txt
* will clean up UTF-8 file, skipping all the invalid characters in the cpp file.
*    -f is the source format
*    -t is the target format
*    -c skips any invalid sequence
*    -o sets for different output file
*
*/

#include <iostream>
#include <cassert>
#include <iomanip>
#include "listdbl.h"
using namespace std;

pNode begin(pList p) {
	return p->head->next;
}

pNode end(pList p) {
	return p->tail;          // not tail->next
}

pNode last(pList p) {
	return p->tail->prev;
}

pNode half(pList p) {  // method 2 - rabbit and turtle
	if(empty(p)) return nullptr;

	pNode rabbit = begin(p);
	pNode turtle = begin(p);
	while(rabbit != end(p) && rabbit != last(p)){
		rabbit = rabbit -> next -> next;
		turtle = turtle -> next;
	}
	return turtle;
}

pNode find(pList p, int val) {
	DPRINT(cout << ">find val=" << val << endl;);
	pNode c = begin(p);
	for (; c != end(p); c = c->next)
		if (c->data == val) return c;

	DPRINT(cout << "<find - not found\n";);
	return c;
}

void clear(pList p) {
	if (empty(p)) return;

	DPRINT(cout << ">clear: ";);
	pNode curr = begin(p);
	pNode head = curr->prev;		// saved head node
	while (curr != end(p)) {
		pNode prev = curr;
		curr = curr->next;
		DPRINT(cout << prev->data << " ";);
		delete prev;
	}
	DPRINT(cout << endl;);

	p->head->next = p->tail;			// set tail at head
	p->tail->prev = p->head;			// set head at tail
	cout << "\tAll things are cleared.\n";
}

bool empty(pList p) {
	return begin(p) == end(p);
}

// returns the number of nodes in the list container.
int size(pList p) {
	int count = 0;
	for (pNode c = begin(p); c != end(p); c = c->next)
		count++;
	return count;
}

//////////////////////////////////////////////////////////////////////////
/////////// Make the best use of the following two fucntions  ////////////
///////////         insert() and erase()                      ////////////
//////////////////////////////////////////////////////////////////////////
void insert(pNode x, int val) {
	DPRINT(cout << ">insert val=" << val << endl;);
	pNode node = new Node{ val, x->prev, x };
	x->prev = x->prev->next = node;
	DPRINT(cout << "<insert\n";);
}

void erase(pNode x) {
	x->prev->next = x->next;
	x->next->prev = x->prev;
	delete x;
}

void erase(pList p, pNode x) {	// checks if x is either tail or head
	if (x == p->tail || x == p->head || x == nullptr) return;
	x->prev->next = x->next;
	x->next->prev = x->prev;
	delete x;
}

/////////////////////// pop ///////////////////////////////////////////////
void pop_front(pList p) {
	DPRINT(cout << ">pop_front\n";);
	if (!empty(p)) erase(begin(p));
	DPRINT(cout << "<pop_front\n";);
}

void pop_back(pList p) {
	DPRINT(cout << ">pop_back\n";);
	if (!empty(p)) erase(end(p)->prev);
	DPRINT(cout << "<pop_back\n";);
}

void pop(pList p, int val) {
	DPRINT(cout << ">pop val=" << val << endl;);
	pNode pos = find(p,val);
	erase(p,pos);
	DPRINT(cout << "<pop\n";);
}

void pop_all(pList p, int val) {
	DPRINT(cout << ">pop_all val=" << val << endl;);
#if 0
	// O(n)
	for (pNode c = begin(p); c != end(p); c = c->next) {
		if(c->data == val) {
			pNode new_c = c -> prev;
			erase(p, c);
			c = new_c;
		}
	} // faster version
#else
	while (find(p, val) != end(p)) {
		pop(p, val);
	} // slower version
#endif
	DPRINT(cout << "<pop_all\n";);
}

// deletes N number of nodes, starting from the end.
// It deletes all the nodes if N is zero which is the default
// or out of the range of the list.  Since it simply calls
// pop_back() which is O(1) repeatedly, it is O(n).
void pop_backN(pList p, int N) {
	DPRINT(cout << ">pop_backN N=" << N << endl;);
	int psize = size(p);
	if (N <= 0 || N > psize) N = psize;
	for (int i = 0; i < N; i++) {
		if (i % 1000 == 0)
			cout << setw(7) << "\r\tpopping [" << psize - i - 1 << "]        ";
		pop_back(p);
	}
	cout << "\n";
	DPRINT(cout << "<pop_backN\n";);
}

/////////////////////// push ///////////////////////////////////////////////
void push_front(pList p, int val) {
	DPRINT(cout << ">push_front val=" << val << endl;);
	insert(begin(p), val);
	DPRINT(cout << "<push_front\n";);
}

void push_back(pList p, int val) {
	DPRINT(cout << ">push_back val=" << val << endl;);
	insert(end(p), val);
	DPRINT(cout << "<push_back\n";);
}

void push(pList p, int val, int x) {
	DPRINT(cout << ">push val=" << val << endl;);
	pNode pos = find(p,x);
	insert(pos,x);
	DPRINT(cout << "<push\n";);
}

unsigned long rand_extended(int range) {
	if (range < RAND_MAX) return rand();
	return rand() * RAND_MAX + rand();
}

void push_backN(pList p, int N) {
	DPRINT(cout << ">push_backN N=" << N << endl;);
	int psize = size(p);
	int range = N + psize;
	srand((unsigned)time(nullptr));

	for(int i = 0; i < N; i++){
		push_back(p, rand_extended(rand()) % range);
	}
	cout << "\n";
	DPRINT(cout << "<push_backN N=" << N << endl;);
}
void push_backN(pList p, int N, int value) {
	DPRINT(cout << ">push_backN N=" << N << "value=" << value << endl;);
	int psize = size(p);
	for (int i = 0; i < N; i++) {
		push_back(p, value);
		if (i % 1000 == 0)
			cout << setw(7) << "\r\tpushing [" << i + psize << "]=" << value << "        ";
	}
	cout << "\n";
	DPRINT(cout << "<push_backN\n";);
}

/////////////////////// unique, reverse, shuffle ///////////////
// removes extra nodes that have duplicate values from the list.
// It removes all but the first node from every consecutive group
// of equal nodes. Notice that a node is only removed from the
// list if it compares equal to the node immediately preceding it.
// Thus, this function is especially useful for sorted lists. O(n)
void unique(pList p) {
	DPRINT(cout << ">unique N=" << size(p) << endl;);
	if (size(p) <= 1) return;

	cout << "your code here\n";

	DPRINT(cout << "<unique";);
}

// reverses the order of the nodes in the list.
// The entire operation does not involve the construction and
// destruction of any element. Nodes are not moved, but poiters
// are moved within the list. O(n)
void reverse(pList p) {
	DPRINT(cout << ">reverse\n";);
	if (size(p) <= 1) return;

	// Using a loop, swap prev and next in every node in the list
	// including two sentinel nodes.
	// Once finished, then, swap two sentinel nodes.

	cout << "your code here\n";

	DPRINT(cout << "<reverse\n";);
}

// returns so called "perfectly shuffled" list. O(n)
// For example, 1234567890 returns 6172839405.
// The first half and the second half are interleaved each other.
// The shuffled list begins with the second half of the original p.
// The entire operation does not involve the construction,
// destruction of any element. It does not invoke insert().
void shuffle(pList p) {
	DPRINT(cout << ">shuffle\n";);
	if (size(p) <= 1) return;    // nothing to shuffle

	cout << "your code here\n";

	DPRINT(cout << "<shuffle\n";);
}

///////////////////////// sort /////////////////////////////////////////////
int ascending (int a, int b) { return a - b; };
int descending(int a, int b) { return b - a; };
int more(int a, int b) { return (a - b); }
int less(int a, int b) { return (b - a); }

// returns the node of which value is larger than x found first,
// the tail sentinel node which is returned by end(p) otherwise.
pNode more(pList p, int z) {
	DPRINT(cout << ">more val=" << z << endl;);
	pNode x = begin(p);
	for (; x != end(p); x = x->next)
		if (x->data > z) return x;

	DPRINT(cout << "<more - not found\n";);
	return x;
}

// returns the node of which value is smaller than x found first,
// the tail sentinel node which is returned by end(p) otherwise.
pNode less(pList p, int z) {
	DPRINT(cout << ">less val=" << z << endl;);
	pNode x = begin(p);
	for (; x != end(p); x = x->next)
		if (x->data > z) return x;

	DPRINT(cout << "<less - not found\n";);
	return x;
}

// returns true if sorted either by either ascending or descending
bool sorted(pList p) {
	DPRINT(cout << ">sorted up or dn\n";);
	return sorted(p, ascending) || sorted(p, descending);
}

// returns true if sorted according to comp fp provided
bool sorted(pList p, int(*comp)(int a, int b)) {
	DPRINT(cout << ">sorted?\n";);
	if (size(p) <= 1) return true;
	pNode curr;
	for(curr = begin(p)->next; curr != end(p); curr = curr->next){
		if(comp(curr->prev->data, curr->data) > 0)
			return false;
	}
	DPRINT(cout << "<sorted: true\n";);
	return true;
}

// inserts a node with val in sorted in the "sorted" list. O(n)
void push_sorted(pList p, int val) {
	DPRINT(cout << "<push_sorted val=" << val << endl;);
	if(sorted(p, ascending))
		insert(more(p,val),val);
	else
		insert(less(p,val),val);
	DPRINT(cout << "<push_sorted\n";);
}

// inserts N number of nodes in sorted in the sorted list.
// If you invoke push_sort() by N times, it takes longer, O(n^2) or
// larger. Therefore, don't call push_sort() N timee or sorted().
// The values for new nodes are randomly generated in the range of
// [0..(N + size(p))]. You may use rand_extended().
void push_sortedN(pList p, int N) {
	DPRINT(cout << "<push_sortedN N=" << N << endl;);
	pNode node;
	int psize = size(p);
	int range = N + psize;

	srand((unsigned)time(NULL));	// initialize random seed
	cout << "your code here\n";
#if 0
	// Slow code example:
	for (int i = 0; i < N; i++) {
		int val = rand_extended(range) % range;
		node = sorted(p, ascending) ? more(p, value) : ::less(p, value);
		insert(node, value);
	}
#else
	cout << "your code here\n";
#endif
	DPRINT(cout << "<push_sortedN\n";);
}

// inserts N number of nodes in sorted in the sorted list.
// The goal of this function is to make it O(n log n).
// Algorithm:
// 1. Generate N numbers to insert. Let's name this array, vals.
// 2. Sort vals using quicksort() of which time complexity
//    is O(n log n), in ascending or descending depending on
//    the list. .
// 3. Merge two lists. - This process is O(n).
//    Compare two values from the list and vals one by one.
//    For example, if sorted ascending and vals is smaller,
//    insert the vals into the list and go for the next val.
//    the list pointer does not increment.
//    If vals is larger, then the list pointer increment, but
//    vals index does not increment.
// 4. If the list is exhausted, then exit the loop. If vals
//    is not exhausted, insert the rest of vals at the end
//    of the list.
//    Make sure that you go through a loop the list and vals
//    together once. This is the same concept used in the
//    most famous "mergesort" algorithm except recursion.
// The values for new nodes are randomly generated in the range of
// [0..(N + size(p))). You may use rand_extended().
void push_sortedNlog(pList p, int N) {
	DPRINT(cout << "<push_sortedNlog N=" << N << endl;);

	int psize = size(p);
	int range = N + psize;
	int* vals = new int[N];

	cout << "your code here\n";

	delete[] vals;
	DPRINT(cout << "<push_sortedNlog\n";);
}

// returns a list of nodes sorted in ascending order if not
// sorted by default, using bubble or selection sort algorithm
// which is O(n^2).
// If the list is already sorted, it reverses the list such that
// the ascending ordered list becomes a descending order list and
// vice versa. It is O(n).
// In the bubble sort, it checks values of two adjacent node
// whether they are in ascending order or not, if not then we
// swap the value. It does this until every element get its right
// position.  In 1st pass the largest value get its right position
// and in 2nd pass 2nd largest value get its position and in 3rd
// pass 3rd largest element get its position and so on.
// void sort(pList p) {
// 	DPRINT(cout << ">sort N=" << size(p) << endl;);
// 	if (sorted(p)) return reverse(p);
// 	bubbleSort(p);
// }

///////////////////////// show /////////////////////////////////////////////

///////////////////////// show //////////////////////////////////////
// shows the values of all the nodes in the list if all is true or
// the list size is less than show_n * 2. If there are more than
// (show_n * 2) nodes, then it shows only show_n number of nodes from
// the beginning and the end in the list.
void show(pList p, bool all, int show_n) {
	DPRINT(cout << "show(" << size(p) << ")\n";);
	if (empty(p)) {
		cout << "\n\tThe list is empty.\n";
		return;
	}
	int i;
	pNode curr;
	const int N = size(p);

	if (all || N < show_n * 2) {
		for (i = 1, curr = begin(p); curr != end(p); curr = curr->next, i++) {
			cout << " -> " << curr->data;
			if (i % show_n == 0) cout << endl;
		}
		if (N % show_n != 0) cout << endl;
		return;
	}

	// print the first show_n data items
	for (i = 1, curr = begin(p); curr != end(p) && i <= show_n; curr = curr->next, i++)
		cout << " -> " << curr->data;

	if (N > show_n * 2)
		cout << "\n...left out..." << half(p)->data << "...left out...";
	cout << "\n";

	// print the last show_n data items
	// move the pointer to the place where show_n data items are left.
	for (i = 1, curr = last(p); curr != begin(p) && i < show_n; i++)
		curr = curr->prev;

	while(curr != end(p)){
		cout << " -> " << curr->data;
		curr = curr -> next;
	}
	cout << "\n";
}
