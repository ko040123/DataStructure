// Note:
// A header file only has to be written once, and it can be included
// in as many files as needed. This also helps with maintenance by
// minimizing the number of changes that need to be made if a
// function prototype ever changes (eg. by adding a new parameter).
// Header files consist of two parts. The first part is called a
// header guard, it prevents a given header file from being
// #included more than once in the same file.
// The second part is the actual content of the.h file, which
// should be the declarations for all of the functions we want
// other files to be able to see. Our header files should all
// have a .h extension, so we��ll call our new header file sort.h:
//
// Have the header guard, #ifndef, unless #pragma once
// By the way, some compilers don't support #pragma.
//
// This is start of the header guard. SORT_H can be any unique name.
// By convention, we use the name of the header file.
#ifndef SORT_H
#define SORT_H

// declare the function prototypes for sort.h
void bubbleSort(int *list, int n);
void insertionSort(int *list, int n);
void quickSort(int *a, int n);
void selectionSort(int *list, int n);

void bubbleSort(int *list, int n, int *(comp)(int, int));

int ascending(int a, int b);
int descending(int a, int b);

// for initial samples 
const int STARTING_SAMPLES = 500;

// This is the end of the header guard
#endif
