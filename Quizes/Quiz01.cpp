/*
On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
Signed: Kim Woo Bin   Student Number: 21600124
*/
#include <iostream>
using namespace std;

int main(){
  int *pi;
  pi = new int;

  *pi = 17;
  cout << "i = " << *pi << endl;

  delete pi;
  return 0;
}

/*
Q1. What type of an error?
A. (1) : a link error.

Q2. Fix the code such that it outputs "i = 17".
1. Adding two lines
2. Using new and delete
*/
