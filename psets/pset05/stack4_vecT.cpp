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

template <typename T>
struct Stack{
	vector<T> item;
};

template <typename T>
using stack = Stack<T> *;

template <typename T>
stack<T> newStack(){
	stack<T> s = new Stack<T>;
	return s;
}

template <typename T>
void free(stack<T> s){delete s;}

template <typename T>
int size(stack<T> s){return s -> item.size();}

template <typename T>
bool empty(stack<T> s){return s -> item.empty();}

template <typename T>
T top(stack<T> s){return s -> item.back();}

template <typename T>
void pop(stack<T> s){s -> item.pop_back();}

template <typename T>
void push(stack<T> s, T item){
	s -> item.push_back(item);
	DPRINT(cout << "\n[ size: " << size(s) << "\tCapa: " << s -> item.capacity() << " ]" << endl;)
}

template <typename T>
void printStack(stack<T> s){
	if(empty(s)) return;
	T temp = top(s);
	cout << temp << " ";
	pop(s);
	printStack(s);
	push(s, temp);
}

template <typename T>
void printStack_fromBottom(stack<T> s){
	if(empty(s)) return;
	T temp = top(s);
	pop(s);
	printStack(s);
	cout << temp << " ";
	push(s, temp);
}

int main(void){
	string list[] = {"to","be","or","not","to","-","be","-","-","that","-","-","-","is"};
	// testBench 1 // string list[] = {"a","b","c","d"};
	stack<string> s = newStack<string>();
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
