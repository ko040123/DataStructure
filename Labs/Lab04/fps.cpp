/*
On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
Signed: Kim Woo Bin   Student Number: 21600124
*/
#include <iostream>
using namespace std;

int fun(int x, int y){
  return x * 2 + y;
}

int foo(int x, int y){
  return x + y * 2;
}

int add(int x, int y){
  return x + y;
}

void op_print(int (*op)(int, int), int a, int b){
  cout << "op(): " << op(a, b) << endl;
}

int main(){
  int (*fps[])(int, int) = {fun, foo, add};

  int N = sizeof(fps) / sizeof(fps[0]);
  for(int i = 0; i < N; i++){
    op_print(fps[i], 2, 3);
  }

}
