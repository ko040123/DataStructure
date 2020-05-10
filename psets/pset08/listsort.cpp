/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/

#include <iostream>
#include "listdbl.h"
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

int ascending(int, int);
int descending(int, int);

// This function takes last element as pivot, places the pivot element at its
// correct position in sorted array, and places all smaller (smaller than pivot)
// to left of pivot and all greater elements to right of pivot
pNode partition(pNode lo, pNode hi, int(*comp)(int, int) = ascending) {
	int x = hi->data;     // set pivot as hi value
	pNode i = lo->prev;   // Index of smaller element

	for (pNode j = lo; j != hi; j = j->next) {
		// If current element is smaller than or equal to pivot
		if (comp(x, j->data) > 0) {
			i = (i == nullptr) ? lo : i->next;    // increment index of smaller element
			std::swap(i->data, j->data);          // Swap current element with index
		}
	}
	i = (i == nullptr) ? lo : i->next;
	std::swap(i->data, hi->data);
	return i;
}

// quickSort helper function for recursive operation
// list[]: array to be sorted, lo: Starting index, h: Ending index
// N is added only for debugging or DPRINT
void quickSort(pNode lo, pNode hi, int(*comp)(int, int) = ascending) {
	if (lo != nullptr && lo != hi && lo != hi->next) {
		pNode p = partition(lo, hi, comp); // Partitioning index
		quickSort(lo, p->prev, comp);
		quickSort(p->next, hi, comp);
	}
}

void quickSort(pList head, int(*comp)(int, int)) {
	quickSort(begin(head), last(head), comp);
}

void bubbleSort(pList p, int(*comp)(int, int)) {
	bool swapped = true;
	DPRINT(cout << ">bubbleSort N=" << size(p) << endl;);
	if (sorted(p)) return reverse(p);

	pNode tail = end(p);
	pNode curr;
	for (pNode i = begin(p); i != end(p) && swapped; i = i->next) {
		swapped = false;
		for (curr = begin(p); curr->next != tail; curr = curr->next) {
			if (comp(curr->data, curr->next->data) > 0) {
				swap(curr->data, curr->next->data);
				swapped = true;
			}
		}
		DPRINT(show(p, false););
		tail = curr;
	}
	DPRINT(cout << "<bubbleSort N=" << size(p) << endl;);
}

void bubbleSort2(pList p, int(*comp)(int, int)) {
	bool swapped;
	DPRINT(cout << ">bubleSort2 N=" << size(p) << endl;);
	if (sorted(p)) return reverse(p);

	pNode tail = end(p);
	do {
		swapped = false;
		pNode curr = begin(p);
		while (curr->next != tail) {
			if (comp(curr->data, curr->next->data) > 0) {
				swap(curr->data, curr->next->data);
				swapped = true;
			}
			curr = curr->next;
		}
		DPRINT(show(p, false););
		tail = curr;
	} while (swapped);
	DPRINT(cout << "<bubbleSort N=" << size(p) << endl;);
}

void insertionSort(pList p, int(*comp)(int, int)) {
	DPRINT(cout << ">insertionSort N=" << size(p) << endl;);
	pNode curr, curr_p;
	int key;
  for(curr = begin(p) -> next; curr != end(p); curr = curr -> next){
		key = curr -> data;
		for(curr_p = curr -> prev; curr_p != begin(p) -> prev; curr_p = curr_p -> prev){
			if(comp(curr_p->data, key) > 0){
				curr_p -> next -> data = curr_p -> data;
			}
			else
				break;
		}
		curr_p -> next -> data = key;
	}

	DPRINT(cout << "<insertionSort N=" << size(p) << endl;);
}

void selectionSort(pList p, int(*comp)(int, int)) {
	DPRINT(cout << ">selectionSort N=" << size(p) << endl;);
  pNode curr, curr_n,min;
	for(curr = begin(p); curr != end(p); curr = curr -> next){
		min = curr;
		for(curr_n = curr -> next; curr_n != end(p); curr_n = curr_n -> next){
			if(comp	(min->data, curr_n->data) > 0)
				min = curr_n;
		}
		swap(curr->data,min->data);
	}

	DPRINT(cout << "<selctionSort N=" << size(p) << endl;);
}

//=========================Quick sort from lab05===============================


int partition(int list[], int lo, int hi, int(*comp)(int, int)) {
	int x = list[hi];  // pivot
	int i = (lo - 1);  // Index of smaller element

	for (int j = lo; j <= hi - 1; j++) {
		// If current element is smaller than or equal to pivot
		if (comp(x, list[j]) > 0) {
			i++;    // increment index of smaller element
			std::swap(list[i], list[j]);  // Swap current element with index
		}
	}
	std::swap(list[i + 1], list[hi]);
	return (i + 1);
}

void _quickSort(int *list, int lo, int hi, int N, int(*comp)(int, int)) {
	if (lo < hi) 	{
		int pi = partition(list, lo, hi, comp); // Partitioning index
		DPRINT(for (int x = 0; x < N; x++) cout << list[x] << " "; cout << endl;);
		_quickSort(list, lo, pi - 1, N, comp);
		_quickSort(list, pi + 1, hi, N, comp);
	}
}

void quickSort(int *a, int n, int(*comp)(int, int)) {
	_quickSort(a, 0, n - 1, n, comp);
}
