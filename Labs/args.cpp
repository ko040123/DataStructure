/*
On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
Signed: Kim Woo Bin   Student Number: 21600124
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string* args_to_strArray(int argc, char** argv);
vector<string> args_to_strVector(int argc, char** argv);
void print_args(string* args, int argc);
void print_args(vector<string> args);


int main(int argc, char** argv){
  string* str = args_to_strArray(argc, argv);
  vector<string> vec = args_to_strVector(argc, argv);

  print_args(str, argc);
  print_args(vec);

  return 0;
}
