/**
Name        : listdblDriver.cpp
Author      : Youngsup Kim, idebtor@gmail.com

04/13/16:	Created
10/20/18:	Added: O(1) options
04/10/18:	added stress test functions more completely
02/10/19:	doubly linked list with sentinel nodes

Description :
: This implements a doubly linked list with two sentinel nodes
: including interactive stress test options.

Note:
For quicksort with a large dataset with the repetition of the same
value, the algorithm requires a large stack.
For example, if there are 50,000 of the same value repeated in the container,
I had to set the stack size to 16M (or 16777216)

For visual studio: Project Properties->Linkers->System->Stack Reserve Size

For g++/MinGW cmd windows, the following command set the stack size to 16M.
  g++ -Wl,--stack,16777216 listdsDriver.cpp listdsx.cpp .......
To check the stack size on Windows, you may use dumpbin that comes with VS

For Mac OSX
  g++ -Wl,-stack_size,0x100000 listdsDriver.cpp listdsx.cpp .......
To check the stack size on OSX
  otool -lv _exefile_name | grep stack
*/

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include "nowic.h"
#include "listdbl.h"
using namespace std;

int main(int argc, char **argv) {
	char c;
	int value, x, N;
	clock_t start = 0;
	bool show_all = false;		// toggle the way of showing values
	int show_n = 12;			// a magic number to begin with 
	pList p = new List();		// create an empty list with two sentinel nodes

	do {
		cout << "\n\tDoubly Linked List( " << size(p)
			 << " nodes, " << show_n << " nodes per line )" << endl;

		cout << "\tf - push front     O(1)\t";	 	 cout << "\tp - pop front   O(1)\n";
		cout << "\tb - push back      O(1)\t"; 		 cout << "\ty - pop back    O(1)\n";
		cout << "\ti - push           O(n)\t"; 		 cout << "\td - pop         O(n)\n";
		cout << "\tz - push sorted    O(n)\t";		 cout << "\te - pop all*    O(n)\n";
		cout << endl;
		cout << "\tS - push sorted N  O(n^2)";       cout << "\ts - sort*       O(n^2)\n";
		cout << "\tZ - push sorted N**O(nlogn)";     cout << "\tu - unique*     O(n)\n";
		cout << "\tB - push back N    O(n)\t";       cout << "\tr - reverse     O(n)\n";
		cout << "\tY - pop  back N    O(n)\t";       cout << "\tx - shuffle**   O(n)\n";
		cout << "\tc - clear          O(n)\t";
		if (show_all)
			cout << "\tt - show [ALL]\n";
		else
			cout << "\tt - show [HEAD/TAIL]\n";
		cout << "\t                       \t";       cout << "\tn - show n nodes per line\n";
		c = GetChar("\tCommand[q to quit]: ");

		switch (c) {	// execute the command
		case 'f':
		case 'b':
		case 'i':
		case 'z':
			value = GetInt("\tEnter a number to push: ");
			switch (c) {
			case 'f':
				push_front(p, value);
				break;
			case 'b':
				push_back(p, value);
				break;
			case 'i':  // push
				x = GetInt("\tChoose a position node: ");
				push(p, value, x);
				break;
			case 'z':  // push_sorted
				if (!empty(p) && !sorted(p)) {
					cout << "\t Run sort first and try it again\n";
					break;
				}
				start = clock();
				push_sorted(p, value);
				break;
			}
			break;

		case 'p':  // deletes the first node in the list
			if (empty(p)) break;
			start = clock();
			pop_front(p);
			break;
		case 'y':  // deletes the last node in the list, O(n)
			if (empty(p)) break;
			pop_back(p);
			break;
		case 'd':  // deletes one node with the value
			if (empty(p)) break;
			value = GetInt("\tEnter a number to pop: ");
			start = clock();
			pop(p, value);
			break;
		case 'e':  // deletes all the nodes with the value given
			if (empty(p)) break;
			value = GetInt("\tEnter a number to pop all: ");
			start = clock();
			pop_all(p, value);
			break;
		case 's':  // sort
			if (empty(p)) break;

			if (sorted(p)) {
				start = clock();
				reverse(p);
			}
			else {
				char ch = GetChar("\tEnter b:bubble, i:insertion, s:selection, q:quick sort: ");
				start = clock();
				switch (ch) {
				case 'b': bubbleSort(p); break;
				case 'i': insertionSort(p); break;
				case 's': selectionSort(p); break;
				case 'q': quickSort(p); break;
				}
			}
			break;
		case 'u':  // unique
			if (empty(p)) break;
			if (!sorted(p)) {
				cout << "\n\tSort first and try it again\n";
				break;
			}
			start = clock();
			unique(p);
			break;

		case 'r':  // reverse
			if (empty(p)) break;
			start = clock();
			reverse(p);
			break;

		case 'x':  // shuffle
			if (empty(p)) break;
			start = clock();
			shuffle(p);
			break;

		case 't': // toggle the way of showing
			show_all ? show_all = false : show_all = true;
			break;

		case 'n': // show_n - n nodes per line
			N = GetInt("\tEnter number of nodes to show per line: ");
			if (N > 0) show_n = N;
			break;

		case 'c':
			if (empty(p)) break;
			start = clock();
			clear(p);
			break;

		case 'S': // push_sortedN  O(n^2)
			if (!empty(p) && !sorted(p)) {
				cout << "\n\tSort first and try it again\n";
				break;
			}
			N = GetInt("\tEnter number of nodes to push sorted?: ");
			start = clock();
			push_sortedN(p, N);
			break;

		case 'Z': // push_sortedNlog  O(n log n)
			if (!empty(p) && !sorted(p)) {
				cout << "\n\tSort first and try it again\n";
				break;
			}
			N = GetInt("\tEnter a number of nodes to push sorted?: ");
			start = clock();

			push_sortedNlog(p, N);

			break;

		case 'B':
			N = GetInt("\tEnter N nodes to push back(-N for a value)?: ");
			if (N > 0) {
				push_backN(p, N);
			}
			else {
				value = GetInt("\tEnter a value to push back?: ");
				start = clock();
				push_backN(p, -N, value);
			}
			break;

		case 'Y':
			if (empty(p)) break;
			N = GetInt("\tEnter a number of nodes to pop back? :");
			start = clock();
			pop_backN(p, N);
			break;
		}

		switch (c) {
		case 'c':
		case 'd':
		case 'e':
		case 'p':
		case 'r':
		case 's':
		case 'u':
		case 'x':
		case 'z':
		case 'B':
		case 'Y':
		case 'S':
		case 'Z':
			cout << "\tcpu: "
				 << ((double) clock() - start) / (double) CLOCKS_PER_SEC << " sec\n";
		default:
			break;
		}
		show(p, show_all, show_n);
	} while (c != 'q');

	clear(p);
	cout << "\n\tJoyful Coding!\n";
	return EXIT_SUCCESS;
}
