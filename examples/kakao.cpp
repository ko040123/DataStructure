#include <string>
#include <iostream>
using namespace std;
#define SIZE 100
#define EOS '$'

class op_stack {
   char s[SIZE];
   int top;

public :
   op_stack();
   void push(char x);
   char pop();
   bool empty();
   char top_element();
};

op_stack::op_stack() {
   top = 0;
}

void op_stack::push(char x) {
   s[top] = x;
   top++;
}

char op_stack::pop() {
   top--;
   return(s[top]);
}

bool op_stack::empty() {
   if (top == 0)
      return true;
   else
      return false;
}

char op_stack::top_element() {
   return(s[top - 1]);
}

bool is_operand(char ch) {
   if ((ch == '(') || (ch == ')') || (ch == '+') || (ch == '-')
      || (ch == '*') || (ch == '/') || (ch == '%') || (ch == '$'))
      return false;
   else
      return true;
}

int get_precendence(char op) {
   if ((op == '$') || (op == '('))
      return(0);
   if ((op == '+') || (op == '-'))
      return(1);
   if ((op == '*') || (op == '/') || (op == '%'))
      return(2);
}

int main() {
   string input, output;
   op_stack stack1;
   op_stack();
   cout << "input an infix expression to convert : ";
   cin >> input;
   input += EOS;
   stack1.push(EOS);
   for (int i = 0; i < input.size(); i++) {
      if (is_operand(input[i]))
         output += input[i];
      else {

         if (input[i] == '(') {
            stack1.push(input[i]);
         }

         else if (input[i] == ')') {
            while (! stack1.empty() && stack1.top_element() != '(') {
               char x = stack1.top_element();
               stack1.pop();
               output += x;
            }
            if (stack1.top_element() == '(')
               char x = stack1.top_element();
               stack1.pop();
         }

         else {
            while (get_precendence(input[i]) <= get_precendence(stack1.top_element())) {

               char x = stack1.top_element();
               stack1.pop();
               output += x;
            }
            stack1.push(input[i]);
         }
      }
   }
   while (stack1.top_element() != '$') {
      char x = stack1.top_element();
      stack1.pop();
      output += x;
   }
   cout << output << endl;
}
