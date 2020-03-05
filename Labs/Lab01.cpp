/*
On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
Signed: Kim Woo Bin   Student Number: 21600124
*/

#include <iostream>
using namespace std;
void sum(int d[], const int& n, int& p){
  p = 0;
  for(int i = 0; i < n; ++i) p = p + d[i];
}

int main(){
  int total = 0;
  int N = 40;
  int *data = new int[N];
  for(int i = 0; i < N; ++i) data[i] = i;
  sum(data, N, total);
  cout << "total is " << total << endl;
  return 0;
}
