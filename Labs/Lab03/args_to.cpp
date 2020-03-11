/*
On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
Signed: Kim Woo Bin   Student Number: 21600124
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string* args_to_strArray(int argc, char** argv){
  string* s = new string[argc];
  for(int i = 0; i < argc; i++){
    s[i] = argv[i];
  }
  return s;
}

vector<string> args_to_strVector(int argc, char** argv){
  vector<string> s;
  for(int i = 0; i < argc; i++){
    s.push_back(argv[i]);
  }
  return s;
}

void print_args(string* args, int argc){
  for(int i = 0; i < argc; i++) cout << "string: "<< args[i] << endl;
  delete[] args;
  args = nullptr;
}

void print_args(vector<string> args){
  for(int i = 0; i < args.size(); i++) cout << "vector: " <<args[i] << endl;
}
