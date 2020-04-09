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

using namespace std;

struct Stack{
	string* item;
	int N;
	int capacity;
};

using stack = Stack*;

stack newStack(int capacity = 1){
	stack s = new Stack;
	s -> item = new string[capacity];
	s -> N = 0;
	s -> capacity = capacity;
	return s;
}

void free(stack s){
	delete[] s -> item;
	delete s;
}

void resize(stack s, int new_capacity){
	string* copied = new string[new_capacity];
	for(int i = 0; i < s -> N; i++)
		copied[i] = s -> item[i];
	delete[] s -> item;
	s -> item = copied;
	s -> capacity = new_capacity;
}

int size(stack s){return s-> N;}

bool empty(stack s){return s -> N == 0;}

void pop(stack s){
	s -> N--;
	if(s -> capacity >= 4 * (s -> N)){
		if(s -> N == 0) return;
		resize(s, (s -> capacity) / 2);
	}
}

string top(stack s){return s -> item[s -> N - 1];}

void push(stack s, string item){
	if(s -> N == s -> capacity){
		resize(s, (s -> capacity) * 2);
	}
	s -> item[s -> N++] = item;
	DPRINT(cout << "\n[ size: " << s -> N << "\tCapa: " << s -> capacity << " ]" << endl;)
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
