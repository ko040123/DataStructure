#include <stdio.h>
#define N 40
void sum(int d[], int n, int* p){
  *p = 0;
  for(int i = 0 ; i < n ; ++i) *p = *p + d[i];
}

int main(){
  int total = 0;
  int data[N];
  for(int i = 0; i < N; ++i) data[i] = i;
  sum(data, N, &total);
  printf("total is %d\n", total);
  return 0;
}

//Use a reference operator, but not a pointer
//Use a const, but not #define
//Use a new operator to allocate an array
//Use cout instead of printf()
//Use a namespace std
