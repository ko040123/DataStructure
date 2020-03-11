/*
On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
Signed: Kim Woo Bin   Student Number: 21600124
*/

#include <iostream>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

void insertionSort(int *list, int n) {
	DPRINT(cout << "INSERTION SORTING...\n");
	for (int i = 1; i < n; i++) {
		int key = list[i];
		int j = i - 1;
		// move elements of list[0..i-1], that are greater than key,
		// to one position ahead of their current position
		while (j >= 0 && key < list[j]) {
			list[j + 1] = list[j];
			j = j - 1;
		}
		list[j + 1] = key;
		DPRINT(for(int x = 0; x < n; x++) cout << list[x] << " "; cout << endl);
	}
}

#if 0


int main() {
	int list[] = { 3, 4, 1, 7, 0, 9, 6, 5, 2, 8};
	int N = sizeof(list) / sizeof(list[0]);
	// int N = 50;
	// int* list = new int[N];
	// for (int i = 0; i < N; i++) list[i] = rand() % N;

	cout << "UNSORTED: " << endl;
	print_list(list, N);

	insertionSort(list, N);

	cout << "INSERTION SORTED: " << endl;
	print_list(list, N);
	// delete[] list;
	cout << "Happy Coding~~\n";
}
#endif
