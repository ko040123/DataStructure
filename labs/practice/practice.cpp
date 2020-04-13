#include <iostream>
#include <string>
#include <stack>

using namespace std;
int count = 0;
string evaluate(string token) {
	stack<string> s;
	string temp, out;

	for (int i = 0; i < token.length(); i++) {
		if (token[i] == ' ') continue;
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
	out = s.top();
	cout << "Process Finished\n";
	return out;
}


int main() {
	string exp, out;

	string postx[] = {"2 3 4 * +", "a b * 5 +", "1 2 + 7 *",
									 "a b c - d + / e a - * c *"};

	string infix[] = {"(2 + (3 * 4))", "((a * b) + 5)", "((1 + 2) * 7)",
										"(((a / ((b - c) + d)) * (e - a)) * c)"};
	for (auto exp : postx) {
		out = evaluate(exp);
		cout << "postx: " << exp << endl;
		cout << "infix: " << out << endl;
	}

	return 0;
}
