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

void bubbleSort(int *list, int n) {
	DPRINT(cout << "BUBBLE SORTING...\n");
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) // last i elements are already in place
			if (list[j + 1] < list[j])
				swap(list[j + 1], list[j]);
		DPRINT(for(int x = 0; x < n; x++) cout << list[x] << " "; cout << endl);
	}
}

#if 0
void print_list(int *list, int n) {
	for (int i = 0; i < n; i++)
		cout << list[i] << " ";
	cout << endl;
}

int main() {
	int list[] = {3, 4, 1, 7, 0, 9, 6, 5, 2, 8};
	int N = sizeof(list) / sizeof(list[0]);
	// int N = 50;
	// int* list = new int[N];
	// for (int i = 0; i < N; i++) list[i] = rand() % N;

	cout << "UNSORTED: " << endl;
	print_list(list, N);

	bubbleSort(list, N);

	cout << "BUBBLE SORTED: " << endl;
	print_list(list, N);
	// delete[] list;
	cout << "Happy Coding~~\n";
}
#endif
