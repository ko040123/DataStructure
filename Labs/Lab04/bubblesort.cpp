/*
On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
Signed: Kim Woo Bin   Student Number: 21600124
*/
#include <iostream>
using namespace std;

int ascend(int a, int b){
 return a - b;
}
int descend(int a, int b){
 return b - a;
}

void bubblesort(int *list, int n, int (*compare)(int a, int b) = ascend){
  int i, j, temp;
  compare(i,j);
  for(i = 0; i < n-1; i++){
    for(j = 0; j < n-1; j++){
      if(compare(list[j],list[j+1]) > 0){
        temp = list[j];
        list[j] = list[j+1];
        list[j+1] = temp;
      }
    }
  }
}

void print_list(int *list, int N){
  for(int i = 0; i < N; i++)
    cout << list[i] << " ";
  cout << endl;
}



int main(){
  int list[] = {2, 8, 1, 9, 5};
  int N = sizeof(list) / sizeof(list[0]);

  cout << "UNSORTED: " << endl;
  print_list(list, N);

  bubblesort(list, N);
  cout << "SORTED Up: " << endl;
  print_list(list, N);

  bubblesort(list, N, descend);
  cout << "SORTED Dn" << endl;
  print_list(list, N);

  return 0;
}
