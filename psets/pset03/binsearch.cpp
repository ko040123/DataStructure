/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/

 /*
 * In this example, you need an extra function at user's convenience since a
 * user may want to simply call the function with three parameters such as
 * binary_search(data, key, size).  Once you get the user's initial call,
 * then you call _binary_search(data, key, low, high) recursively.

 * int _binary_search(int *list, int key, int lo, int hi)
 * implements a recursive binary search algorithm.
 * INPUT:
 *		*list is a array of integers SORTED in ASCENDING order,
 *		key is the integer to search for, lo is the minimum
 *    array index, hi is the maximum array index
 * OUTPUT:
 *		returns the array index of `key` in the list' if found.
 *		otherwise returns a modified index where it could be found.
 * NOTE:
 * If the key is not found, low is the insertion point where a key would be
 * inserted to maintain the order of the list.  It is more useful to return
 * the insertion point than -1.  The method must return a negative value to
 * indicate that the key is not in the list. Can it simply return -low?
 */

#include <iostream>
#include <iomanip>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

int _binary_search(int *data, int key, int lo, int hi) {
	DPRINT(cout << "key=" << key << " lo=" << lo << " hi=" << hi << endl;);

	if(lo > hi) return (lo + 1) * (-1);
	int mi = (lo + hi) / 2;
	if(key == data[mi]) return mi;
	if(key < data[mi]) return _binary_search(data, key, lo, mi - 1);
	else return _binary_search(data, key, mi + 1, hi);
}

int binary_search(int *list, int key, int size) {
	DPRINT(cout << ">binary_search: key=" << key << " size=" << size << endl;);
	int answer = _binary_search(list, key, 0, size);
	DPRINT(cout << "<binary_search: answer=" << answer << endl;);
	return answer;
}

#if 0
int main(int argc, char *argv[]) {
	int list[] = { 3, 5, 6, 9, 11, 12, 15, 18, 19, 20 };
	// int list[] = { 13, 15, 16, 19, 21, 22, 25, 28, 29, 30 };  // test set
	// int list[] = { 53, 55, 56, 59, 61, 62, 65, 68, 69, 70 };  // test set
	int size = sizeof(list) / sizeof(list[0]);

	cout << "list: ";
	for (int i = 0; i < size; i++)
		cout << list[i] << " ";
	cout << endl;

	// randomly generate numbers to search between
	// list[0] and list[size-1], inclusviely.
	// do this by 'size' times.
	// print the results as shown in binsearchx.exe.
	srand((unsigned)time(nullptr));

	for (int i = 0; i < size; i++) {
		int find_num = list[0] + (rand() % (list[size-1] - list[0] + 1));
		int ans = binary_search(list, find_num, size);
		if(ans < 0)
			cout <<"\t"<< find_num <<"\tis not @["<< (-1) * (ans + 1) <<"]"<< endl;
		else
			cout <<"\t"<< find_num <<"\tis @["<< ans <<"]"<< endl;
	}

}
#endif
