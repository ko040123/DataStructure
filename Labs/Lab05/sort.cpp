/*
On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
Signed: Kim Woo Bin   Student Number: 21600124
*/

// To compile all sort files
// g++ sort.cpp bubble.cpp insertion.cpp quicksort.cpp selection.cpp
//     print_list.cpp -I../../include -o sort -DDEBUG

#include <iostream>
#include <cassert>
#include "sort.h"
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

void print_list(int *list, int n);

int main(int argc, char *argv[]) {
	int unsorted[] = { 3, 4, 1, 7, 0, 9, 6, 5, 2, 8};
	int N = sizeof(unsorted) / sizeof(unsorted[0]);

	// make a list to save the data
	int *list = new (nothrow) int[N];
	assert(list != nullptr);

	while (1) {
		// set a list to sort from unsorted.
		for (int i = 0; i < N; i++) list[i] = unsorted[i];

		// ask user to choose a sort algorithm
		char algo;
		cout << "b for bubble, i for insertion, q for quick, s for selection \n";
		cout << "Enter an algorithm to sort(x to exit): ";
		cin >> algo;
		if (algo == 'x') break;
		if (algo != 'b' && algo != 'i' && algo != 'q' && algo != 's') {
			cout << "The sort algorithm must be one of (b, i, q, s).\n";
			break;
		}

		cout << "UNSORTED(" << N << "):\n";
		print_list(list, N);

		switch(algo) {
			case 'b': bubbleSort(list, N);
								break;
			case 'i': insertionSort(list, N);
								break;
			case 'q': quickSort(list, N);
								break;
			case 's': selectionSort(list ,N);
								break;
			default: break;
		}

		cout << "SORTED(" << N << "):\n";
	    print_list(list, N);
	}

	delete[] list;   // free resources
  cout << "Happy Coding~~\n";
}
