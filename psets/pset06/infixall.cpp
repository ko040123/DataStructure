/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/

#include <iostream>
#include <cassert>
#include <stack>
using namespace std;

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
// Stay tuned since we are going to use C++ Template to make them into
// one or a generic function.
// prints stack items from botton to top recursively.
void printStack(stack<int> s) {
	stack<int> temp;
	while (!s.empty()) {
		temp.push(s.top());
		s.pop();
	}
	while (!temp.empty()) {
		cout << temp.top() << " ";
		s.push(temp.top());
		temp.pop();
	}
}

void printStack(stack<char> s) {
	stack<char> temp;
	while (!s.empty()) {
		temp.push(s.top());
		s.pop();
	}
	while (!temp.empty()) {
		cout << temp.top() << " ";
		s.push(temp.top());
		temp.pop();
	}
}

int cal_precedence(char op) {
	switch (op) {
	case '(': return 1;
	case '+': return 2;
	case '-': return 2;
	case '*': return 3;
	case '/': return 3;
	case '^': return 4;
	}
	cout << "Something Wrong with CAL_PRECEDENCE\n";
	return 0;
}

// performs arithmetic operations.
int apply_op(int a, int b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	case '^': {
		int ans = 1;
		for (int i = 0; i < b; i++) {
			ans *= a;
		}
		return ans;
	}
	}
	cout << "nsupported operator encountered: " << op << endl;
	return 0;
}

int compute(stack<int>& va_stack, stack<char>& op_stack) {
	int right = va_stack.top(); va_stack.pop();
	int left = va_stack.top(); va_stack.pop();
	char op = op_stack.top(); op_stack.pop();
	int answer = apply_op(left, right, op);
	DPRINT(cout << " va/op_stack.pop: " << left << op << right << " = " << answer << endl;);
	return answer;
}

// returns value of expression after evaluation.
int evaluate(string token) {
	DPRINT(cout << ">evaluate: token=" << token << endl;);

	stack<int>  va_stack;                 // stack to store operands or values
	stack<char> op_stack;                 // stack to store operators.

	for (unsigned int i = 0; i < token.length(); i++) {
		DPRINT(cout << " token[" << i << "]=" << token[i] << endl;);


		// current token is a whitespace or an opening brace, skip it.
		if (token[i] == ' ') continue;
		if (token[i] == '(') {
			op_stack.push(token[i]);
			DPRINT(cout << " op_stack.push: " << token[i] << endl;);
			continue;
		}

		// current token is a value(or operand), push it to va_stack.
		if (isdigit(token[i])) {
			int count = 0;
			int va;
			va = token[i++] - '0';
			while (isdigit(token[i])) {
				count++;
				int temp = token[i++] - '0';
				va = va * 10 + temp;
			}
			i--;
			va_stack.push(va);
			DPRINT(cout << " va_stack.push: " << va << endl;);

		} // closing brace encountered; compute it and push the result to va_stack.
		else if (token[i] == ')') {
			while (!(op_stack.top() == '(')) {
				int answer = compute(va_stack, op_stack);
				va_stack.push(answer);
				DPRINT(cout << " va_stack.push: " << answer << endl;);
			}
			DPRINT(cout << " op_stack.pop: " << op_stack.top() << endl;);
			op_stack.pop();
		}
		else { // current token is an operator; push it to op_stack.
			while (!op_stack.empty() && cal_precedence(op_stack.top()) >= cal_precedence(token[i])) {
				int answer = compute(va_stack, op_stack);
				va_stack.push(answer);
				DPRINT(cout << " va_stack.push: " << answer << endl;);
			}
			op_stack.push(token[i]);
			DPRINT(cout << " op_stack.push: " << token[i] << endl;);

		}
	}

	DPRINT(cout << "Token is cleared. Now, check two stacks:" << endl;);
	DPRINT(printStack(va_stack);  cout << endl;);
	DPRINT(printStack(op_stack);  cout << endl;);

	// The whole expression has been parsed at this point,
	// apply remaining op_stack to remaining va_stack.
	while (!op_stack.empty()) {
		int answer = compute(va_stack, op_stack);
		va_stack.push(answer);
		DPRINT(cout << " va_stack.push: " << answer << endl;);
	}

	// use two post-conditions for assertion
	assert(op_stack.empty());
	assert(va_stack.size() == 1);

	// va_stack top contains the result, return it.
	DPRINT(cout << "<evaluate" << endl;);
	return va_stack.top();
}
