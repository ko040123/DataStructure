/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/

/*
* To build this program:
*  g++ recursionDriver.cpp recursion.cpp binsearch.cpp mergesort.cpp
*      -I../include -L../lib -lnowic -o recursion
*/

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

#include <iostream>
#include <cassert>
#include <iomanip>

using namespace std;

#include "nowic.h"

long long factorial(int N);
long long fibonacci(int N);
int gcd(int a, int b);
int bunnyEars(int a);
int funnyEars(int a);
int triangle(int a);
int sumDigits(int n);
int count8(int n);
long long powerN(int base, int n);

int binary_search(int* list, int key, int N);
int mergeSort(int* list, int* aux, int N, int lo, int hi);

// merge_sort interface with mergeSort() described in the lecture PPT.
void merge_sort(int* list, int N) {
	int* aux = new (nothrow) int[N];
	assert(aux != nullptr);

	mergeSort(list, aux, N, 0, N - 1);

	delete[] aux;
}

int main(int argc, char *argv[]) {
	int option;
	int N;

	// Use setvbuf() to prevent the output from buffered on console.
	setvbuf(stdout, NULL, _IONBF, 0);

	while(1) {
		cout << "\n\tRecursive Algorithms:\n"
			"\t1. Factorial\n"
			"\t2. GCD(Great Common Divisor)\n"
			"\t3. Fibonacci\n"
			"\t4. Bunny Ears\n"
			"\t5. Funny Ears\n"
			"\t6. Triangle\n"
			"\t7. Sum of digits\n"
			"\t8. Count 8\n"
			"\t9. Power N\n"
			"\t10. Recursive Binary Search\n";

		switch (option = GetInt("\tCommand(0 to quit): ")) {
		case 0:
			cout << "Happy Coding~~\n";
			exit(EXIT_SUCCESS);

		case 1:
			cout << "\tFactorial Examples:\n";
			cout << "\tfactorial(1) = 1\n";
			cout << "\tfactorial(2) = 2\n";
			cout << "\tfactorial(3) = 6\n";
			cout << "\tfactorial(8) = 40320\n";
			cout << "\tfactorial(12) = 479001600\n";

			while (1) {
				N = GetInt("\tEnter a number to compute N factorial(0 to quit): ");
				if (N <= 0) break;
				cout << "\tfactorial(" << N << ") = " << factorial(N) << endl;
			}
			break;
		case 2:
			cout << "\tGCD Examples:\n";
			cout << "\tgcd(27, 9) = 9\n";
			cout << "\tgcd(111, 259) = 37\n";

			while (1) {
				int x = GetInt("\tEnter 1st number to compute GCD(0 to quit): ");
				if (x == 0) break;
				int y = GetInt("\tEnter 2nd number to compute GCD(0 to quit): ");
				if (y == 0) break;
				cout << "\tgcd(" << x << ", " << y << ") = " << gcd(x, y) << endl;
			}
			break;

		case 3:
			cout << "\tFibonacci Examples:\n";
			cout << "\tfibonacci(0) = 0\n";
			cout << "\tfibonacci(1) = 1\n";
			cout << "\tfibonacci(2) = 1\n";
			cout << "\tfibonacci(3) = 2\n";
			cout << "\tfibonacci(4) = 3\n";
			cout << "\tfibonacci(5) = 5\n";
			cout << "\tfibonacci(6) = 8\n";
			while (1) {
				N = GetInt("\tEnter a number to compute N fibonacci(0 to quit): ");
				if (N <= 0) break;
				cout << "\tfibonacci(" << N << ") = " << fibonacci(N) << endl;
			}
			break;
		case 4:
			cout << "\tBunnyEars Examples:\n";
			cout << "\tbunnyEars(0) = 0\n";
			cout << "\tbunnyEars(1) = 2\n";
			cout << "\tbunnyEars(2) = 4\n";
			cout << "\tbunnyEars(3) = 6\n";
			cout << "\tbunnyEars(234) = 468\n";
			while (1) {
				N = GetInt("\tEnter a number of bunnies(0 to quit): ");
				if (N <= 0) break;
				cout << "\tbunnyEars(" << N << ") = " << bunnyEars(N) << endl;
			}
			break;
		case 5:
			cout << "\tFunnyEars Examples:\n";
			cout << "\tfunnyEars(0) = 0\n";
			cout << "\tfunnyEars(1) = 2\n";
			cout << "\tfunnyEars(2) = 5\n";
			cout << "\tfunnyEars(3) = 7\n";
			cout << "\tfunnyEars(4) = 10\n";
			cout << "\tfunnyEars(9) = 22\n";
			while(1){
				N = GetInt("\tEnter a number of funnies(0 to quit): ");
				if (N <= 0) break;
				cout << "\tfunnyEars(" << N << ") = " << funnyEars(N) << endl;
			}
			break;
		case 6:
			cout << "\tTriangle Examples\n";
			cout << "\ttriangle(0) = 0\n";
			cout << "\ttriangle(1) = 1\n";
			cout << "\ttriangle(2) = 3\n";
			cout << "\ttriangle(3) = 6\n";
			cout << "\ttriangle(4) = 10\n";
			cout << "\ttriangle(7) = 28\n";
			while(1){
				N = GetInt("\tEnter a number of rows(0 to quit): ");
				if (N <= 0) break;
				cout << "\ttriangle(" << N << ") = " << triangle(N) << endl;
			}
			break;
		case 7:
			cout << "\tSum of digits Examples\n";
			cout << "\tsumDigits(126) = 9\n";
			cout << "\tsumDigits(49) = 13\n";
			cout << "\tsumDigits(12) = 3\n";
			cout << "\tsumDigits(1) = 1\n";
			cout << "\tsumDigits(0) = 0\n";
			cout << "\tsumDigits(10110) = 3\n";
			cout << "\tsumDigits(235) = 10\n";
			while(1){
				N = GetInt("\tEnter a Digit(0 to quit): ");
				if (N <= 0) break;
				cout << "\tsumDigits(" << N << ") = " << sumDigits(N) << endl;
			}
			break;
		case 8:
			cout << "\tCount 8 Examples\n";
			cout << "\tcount8(818) = 2\n";
			cout << "\tcount8(8) = 1\n";
			cout << "\tcount8(123) = 0\n";
			cout << "\tcount8(881238) = 3\n";
			cout << "\tcount8(48581) = 2\n";
			cout << "\tcount8(888586198) = 5\n";
			cout << "\tcount8(99899) = 1\n";
			while(1){
				N = GetInt("\tEnter a number(0 to quit): ");
				if (N <= 0) break;
				cout << "\tcount8(" << N << ") = " << count8(N) << endl;
			}
			break;
		case 9:
			cout << "\tPower N Examples\n";
			cout << "\tpowerN(2,5) = 32\n";
			cout << "\tpowerN(3,1) = 3\n";
			cout << "\tpowerN(3,2) = 9\n";
			cout << "\tpowerN(3,3) = 27\n";
			cout << "\tpowerN(10,2) = 100\n";
			cout << "\tpowerN(10,3) = 1000\n";
			while (1) {
				int x = GetInt("\tEnter a base (0 to quit): ");
				if (x == 0) break;
				int y = GetInt("\tEnter N (0 to quit): ");
				if (y == 0) break;
				cout << "\tpowerN(" << x << ", " << y << ") = " << powerN(x, y) << endl;
			}
			break;

		case 10:
			cout << "\tRecursive Binary Search\n ";
			while (1) {
				N = GetInt("\tEnter a list size to generate(0 to quit) : ");
				if (N <= 0) break;

				int *list = new (nothrow) int[N];
				assert(list != nullptr);

				srand((unsigned)time(nullptr));
				for (int i = 0; i < N; i++)
					list[i] = rand() % N;

				merge_sort(list, N);
				cout << "\t";
				for (int i = 0; i < N; i++) cout << list[i] << " ";
				cout << endl;

				int key = GetInt("\tEnter a number to search: ");
				int index = binary_search(list, key, N);
				if(index < 0)
					cout <<"\t"<< key <<"\tis not @["<< (-1) * (index + 1) <<"]"<< endl;
				else
					cout <<"\t"<< key <<"\tis @["<< index <<"]"<< endl;
				delete[] list;
			}
		default:
			break;
		}
	};

	cout << "Happy Coding~~\n";
	return EXIT_SUCCESS;
}
