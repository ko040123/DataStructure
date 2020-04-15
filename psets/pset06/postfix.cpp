/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/

#include <iostream>
#include <cassert>
using namespace std;
#include <stack>


#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

#if 0
/////////////////////////////////////////////////////////////////////////////////
// a basic stack functinality only provided for pedagogical purpose
// To use STL stack, just comment out this section and inclucde <stack> above.
#include <vector>
template <typename T>
struct stack {
	vector<T> item;

	bool empty() const {
		return item.empty();
	}
	auto size() const {
		return item.size();
	}
	void push(T const& data) {
		item.push_back(data);
	}
	void pop() {
		if (item.empty())
			throw out_of_range("stack<>::pop(): pop stack");
		item.pop_back();
	}
	T top() const {
		if (item.empty())
			throw out_of_range("stack<>::top(): top stack");
		return item.back();
	}
};
///////////////////////////////////////////////////////////////////////
#endif

void printStack(stack<string> orig) {
	stack<string> temp;
	while (!orig.empty()) {
		temp.push(orig.top());
		orig.pop();
	}
	while (!temp.empty()) {
		cout << temp.top() << " ";
		orig.push(temp.top());
		temp.pop();
	}
}

// returns an infix expression after postfix evaluation.
string evaluate(string token) {
	stack<string> s;
	string temp, out;
	DPRINT(cout << ">evaluate(): token=" << token << endl;);

	for (unsigned int i = 0; i < token.length(); i++) {
		DPRINT(cout << " token[" << i << "]=" << token[i] << endl;);
		// current token is a whitespace or an opening brace, skip it.
		if (token[i] == ' ') continue;
		if (token[i] == '(') continue;
		if (token[i] == '+' || token[i] == '-' || token[i] == '*' || token[i] == '/') {
			temp = s.top();
			s.pop();
			out = '(' + s.top() + token[i] + temp + ')';
			s.pop();
			s.push(out);
			continue;
		}
		temp = token[i];
		s.push(temp);

	}
	DPRINT(cout << "--token exhausted---\n";);
	DPRINT(cout << "--checking the stack, its size() should be 1---\n";);
	DPRINT(printStack(s); cout << endl;);
	DPRINT(cout << "--the stack is checked---\n";);

 	// change assert to check the post condition using the stack size
	assert(s.size() == 1);

	out = s.top();

	DPRINT(cout << "<evaluate() returns "  << out << endl;);
	return out;
}
