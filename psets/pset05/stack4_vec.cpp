/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/
#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

#include <iostream>
#include <vector>

using namespace std;

struct Stack{
	vector<string> item;
};

using stack = Stack*;

stack newStack(){
	stack s = new Stack;
	return s;
}

void free(stack s){delete s;}

int size(stack s){return s -> item.size();}

bool empty(stack s){return s -> item.empty();}

string top(stack s){return s -> item.back();}

void pop(stack s){s -> item.pop_back();}

void push(stack s, string item){
	s -> item.push_back(item);
	DPRINT(cout << "\n[ size: " << size(s) << "\tCapa: " << s -> item.capacity() << " ]" << endl;)
}

void printStack(stack s){
	if(empty(s)) return;
	string temp = top(s);
	cout << temp << " ";
	pop(s);
	printStack(s);
	push(s, temp);
}

void printStack_fromBottom(stack s){
	if(empty(s)) return;
	string temp = top(s);
	pop(s);
	printStack(s);
	cout << temp << " ";
	push(s, temp);
}

int main(void){
	string list[] = {"to","be","or","not","to","-","be","-","-","that","-","-","-","is"};
	// testBench 1 // string list[] = {"a","b","c","d"};
	stack s = newStack();
	for(auto item : list){
		if(item != "-"){
			push(s, item);
		}
		else{
			cout << top(s) << " ";
			pop(s);
		}
	}

	cout << "\nsize: " << size(s);
	cout << "\ntop: " << top(s);
	cout << "\nstack T: "; printStack(s);
	cout << "\nstack B: "; printStack_fromBottom(s);
	cout << "\nHappy Coding~";

	free(s);
	return 0;
}
