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
