/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/

/*
*
* Before Compilation, you must have some files (static library and
* include file) ready as shown below:
*   src/selection.cpp, bubble.cpp ...
*   include/nowic.h
*	lib/libnowic.a        (nowic.lib for Visual Studio)
* Compilation:
*	g++ selection.cpp insertion.cpp quicksort.cpp bubble.cpp
*       sortDriver.cpp -I../include -L../lib -lnowic -o sort
*/

#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include "nowic.h"

using namespace std;

void bubbleSort(int *list, int n);
void insertionSort(int *list, int n);
void quickSort(int *list, int n);
void selectionSort(int *list, int n);
void _printList(int *list, int start, int end, int per_line);
void printList(int *list, int n, int max_print, int per_line);
void randomize(int list[], int n);

void randomize(int list[], int n) {
	DPRINT(cout << ">randomize...N=" << n << endl;)
	srand((unsigned)time(nullptr)); // random seed를 누적 time 값으로 해서 중복되지 않게 한다.
	int temp, rand_idx;

	for(int i = 0; i < n; i++){
		rand_idx = rand() % n; // modulo 값으로 바꿔줄 index 찾는다.
		temp = list[i];
		list[i] = list[rand_idx];
		list[rand_idx] = temp;
	}

	DPRINT(cout << "<randomize" << endl;)
}

void _printList(int *list, int start, int end, int per_line){
	int count = 1;
	for(int i = start; i < end; i++, count++){
		cout << "\t" << list[i];
		if(per_line == count) cout << endl;
	}
	cout << endl;
}

void printList(int *list, int N, int max_print, int per_line) {
	DPRINT(cout << ">printList...N=" << N << " max_print=" << max_print << endl;)
	if(max_print >= N) max_print = N / 2; //max_print가 N이상이면 N/2로 설정.

	_printList(list, 0, max_print, per_line);
	_printList(list, N - max_print, N, per_line);

	DPRINT(cout << "<printList" << endl;)
}

// sortDriver to test sort functions or algorithms.
int main(int argc, char *argv[]) {
	int N = 0;						// default sample size
	int keyin;
	int *list = nullptr;				// input and output buffer
	int max_print = 10;				// default max_print(=front_part+last_part)
	int per_line = max_print / 2;	// default samples per line to print
	clock_t start, end;
	char randomized = 'N';
	char option_char;
	char option_str[512];
	char algorithm_list[4][20] = {"Bubble", "Insertion", "Quicksort", "Selection"};
	enum algorithm_enum { BUBBLE, INSERTION, QUICKSORT, SELECTION };
	int  algorithm_chosen = SELECTION;  // default algorithm chosen
  void (*sortFn)(int *, int) = selectionSort; // Function pointer 생성

	DPRINT(cout << ">main...N=" << N << endl;)

	// Use setvbuf() to prevent the output from buffered on console.
	setvbuf(stdout, NULL, _IONBF, 0);

	do {
		//sprintf를 통해 option_str 문자열 안에 숫자 값들을 넣어준다.
		sprintf(option_str, "[sort=%s N=%d randomized=%c max_print=%d per_line=%d]",
			algorithm_list[algorithm_chosen], N, randomized, max_print, per_line);

		cout << "\n\tOPTIONS: " << option_str << "\n"
			"\tn - number of samples size and initialize\n"
			"\tr - randomize(shuffle) samples\n"
			"\ta - algorithm to run\n"
			"\ts - sort()\n"
			"\tm - max samples to display at front or rear\n"
			"\td - max samples to display per line\n";


		option_char = GetChar("\tCommand(q to quit): ");
		DPRINT(cout << "option_char = " << option_char << endl;)

		switch (option_char) {
		case 'a': DPRINT(cout << "case = " << option_char << endl;)

			switch (GetChar("\tEnter b for bubble, i for insertion, s for selection, q for quick sort: ")) {
			// your code here
			case 'b':
				sortFn = bubbleSort;
        algorithm_chosen = BUBBLE;
				break;
			case 'i':
				sortFn = insertionSort;
        algorithm_chosen = INSERTION;
				break;
			case 's':
				sortFn = selectionSort;
        algorithm_chosen = SELECTION;
				break;
			case 'q':
				sortFn = quickSort;
        algorithm_chosen = QUICKSORT;
				break;

			default: { cout << "\n\tNo such an algorithm available. Try it again.\n"; break; }
			}
			break;

		case 'n': DPRINT(cout << "case = " << option_char;)

			keyin = GetInt("\tEnter input sample size: ");
			if (keyin < 1) {
				cout << "\tExpecting a number larger than 0\n";
				break;
			}

			// Set N with the new keyin value.
			N = keyin;
			// Deallocate the old list if not nullptr
			if(list != nullptr){
				delete[] list;
			}
			// before allocating the new list,
			// Allocate memory for new data samples using new.
			list = new int[N];
			// Fill the list with numbers from 0 to N - 1.
			for(int i = 0; i < N; i++) list[i] = i;
			randomized = 'N' ;
			printList(list, N, max_print, per_line);
			break;

		case 'r': DPRINT(cout << "case = " << option_char << endl;)
			if (N <= 1) {
				cout << "\tSet sample size first or larger\n";
				break;
			}
			// list의 내용을 랜덤하게 셔플.
			randomize(list, N);
			randomized = 'Y';
			printList(list, N, max_print, per_line);
			break;

		case 's': DPRINT(cout << "case = " << option_char << endl;)
			if (N <= 0) {
				cout << "\tSet sample size first\n";
				break;
			}
			cout << "\tThe clock ticks and " << algorithm_list[algorithm_chosen] << " begins...\n";
			start = clock();
      sortFn(list, N);
			end = clock();
			printList(list, N, max_print, per_line);
			cout << "\tDuration: " << (end - start) / (double)CLOCKS_PER_SEC << " seconds\n";
			break;

		case 'm': {DPRINT(cout << "case = " << option_char << endl;)
			int temp_max_print = GetInt("\tEnter max sample size to display: ");
			if (temp_max_print < 1) {
				cout << "\tExpecting a number larger than 0\n";
				break;
			}
			max_print = temp_max_print;
			printList(list, N, max_print, per_line);
			break;
		}

		case 'd': {DPRINT(cout << "case = " << option_char << endl;)
			int temp_per_line = GetInt("\tEnter max sample per line to display: ");
			if (temp_per_line < 1) {
				cout << "\tExpecting a number larger than 0\n";
				break;
			}
			per_line = temp_per_line;
			printList(list, N, max_print, per_line);
			break;
		}


		default:
			break;
		}
	} while (option_char != 'q');

	if (list != nullptr) delete[] list;
	// system("pause");
	DPRINT(cout << ">main" << endl;)
	return EXIT_SUCCESS;
}
