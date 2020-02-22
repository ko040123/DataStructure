/*
On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
Signed: Kim Woo Bin   Student Number: 21600124
*/

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){

  if(argc == 1){
    string name = "default";

    while(true){
      cout << "Enter a name: ";
      getline(cin, name);

      if(name == "") break;
      else cout << "Hello " << name << "!\n";
    }
  }

  else{
    for(int i = 1; i < argc; i++) cout << "Hello "<< argv[i] <<"!\n";
  }

  cout << "Hello World!\n";
  return 0;
}
