// quicksort.cpp by idebtor@gmail.com
// A typical recursive implementation of quick sort
// 2018.12.15 - Creation
/*
* Compilation:
* g++ quicksort.cpp -o sort
* g++ quicksort.cpp -o sort -DDEBUG
* To use DEBUG or test it, compile with -D option and turn #if 1 on.
* To make the function included in other program, turn #if 0 off.
*/

#include <iostream>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif
//
int ascending(int, int);
int descending(int, int);

// This function takes last element as pivot, places the pivot element at its
// correct position in sorted array, and places all smaller (smaller than pivot)
// to left of pivot and all greater elements to right of pivot.
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

// quickSort helper function for recursive operation
// list[]: array to be sorted, lo: starting index, h: ending index
// N is added only for debugging or DPRINT
void _quickSort(int *list, int lo, int hi, int N, int(*comp)(int, int)) {
	if (lo < hi) 	{
		int pi = partition(list, lo, hi, comp); // Partitioning index
		DPRINT(for (int x = 0; x < N; x++) cout << list[x] << " "; cout << endl;);
		_quickSort(list, lo, pi - 1, N, comp);
		_quickSort(list, pi + 1, hi, N, comp);
	}
}

void quickSort(int *a, int n, int(*comp)(int, int) = ascending) {
	_quickSort(a, 0, n - 1, n, comp);
}


/*------------------------------------------------------------------------------
void print_list(int *list, int n);

int partition(int list[], int lo, int hi) {
	int x = list[hi];  // pivot
	int i = (lo - 1);  // Index of smaller element

	for (int j = lo; j <= hi - 1; j++) {
		if (list[j] <= x) { 				// if current element is <= pivot
			i++;    									// increment index of smaller element
			swap(list[i], list[j]);  	// Swap current element with index
		}
	}
	swap(list[i + 1], list[hi]);
	return (i + 1);
}

// QuickSort helper function for recursive operation
// list[]: array to be sorted, lo: Starting index, h: Ending index
// N is added only for debugging or DPRINT
void _quickSort(int *list, int lo, int hi, int n) {
	if (lo < hi) 	{
		int pi = partition(list, lo, hi); // Partitioning index
		DPRINT(for(int x = 0; x < n; x++) cout << list[x] << " "; cout << endl);
		_quickSort(list, lo, pi - 1, n);
		_quickSort(list, pi + 1, hi, n);
	}
}

void quickSort(int *a, int n) {
	DPRINT(cout << "QUICK SORTING...\n");
	_quickSort(a, 0, n - 1, n);  // the last argument n is added only for DPRINT()
}

#if 0
void print_list(int *list, int n) {
	for (int i = 0; i < n; i++)
		cout << list[i] << " ";
	cout << endl;
}
#endif

#if 0
int main() {
	int list[] = { 3, 4, 1, 7, 0, 9, 6, 5, 2, 8};
	int N = sizeof(list) / sizeof(list[0]);
	// int N = 50;
	// int* list = new int[N];
	// for (int i = 0; i < N; i++) list[i] = rand() % N;

	cout << "UNSORTED: " << endl;
	print_list(list, N);

	quickSort(list, N);

	cout << "QUICK SORTED: " << endl;
	print_list(list, N);
	// delete[] list;
	cout << "Happy Coding~~\n";
}
#endif
*/
