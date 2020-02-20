#include <iostream>
using namespace std;

void double_by_ptr(int *x){
  *x = *x * 2;
}
void double_by_ref(int& y){
  y = y * 2;
}
int double_by_val(int z){
  return z * 2;
}

int main(){
  int x = 2, y = 3, z = 4;
  double_by_ptr(&x);
  cout << x << endl;

  double_by_ref(y);
  cout << y << endl;

  z = double_by_val(z);
  cout << z << endl;
}
