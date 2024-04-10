#include <iostream>
#include <stack>

using namespace std;

int applyOperator(int a, int b, char op);
int applyOperator_util(stack<int>& values, stack<char>& ops);
int precedence(char op);
int evaluate(string expression);

int main() {
  string tests[] = {"99 - 8 * (22 - 3)", "129-345+12",
                    "129 * (22 - 1 * (22 + 1) / (0 - 1))", "123 * 34 / 56 - 1"};
  for (string& str : tests) cout << str << ": \t" << evaluate(str) << endl;
  return 0;
}

int applyOperator(int a, int b, char op) {
  switch (op) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      return a / b;
    default:
      throw "The supported operations is: [+,-,*,/]";
  }
}

int applyOperator_util(stack<int>& values, stack<char>& ops) {
  int v2 = values.top();
  values.pop();
  int v1 = values.top();
  values.pop();
  char op = ops.top();
  ops.pop();
  return applyOperator(v1, v2, op);
}

int precedence(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    default:
      return 0;
  }
}

// it is used te shuntig yard algorithm
int evaluate(string expression) {
  int i;
  stack<int> values;
  stack<char> operators;
  for (int i = 0; i < expression.length(); i++) {
    if (expression[i] == ' ')
      continue;
    else if (expression[i] == '(')
      operators.push('(');
    else if (isdigit(expression[i])) {
      int val = 0;
      while (i < expression.length() && isdigit(expression[i]))
        val = 10 * val + expression[i++] - '0';
      values.push(val);
      i--;
    } else if (expression[i] == ')') {
      while (!operators.empty() && operators.top() != '(')
        values.push(applyOperator_util(values, operators));
      if (!operators.empty()) operators.pop();
    } else {
      while (!operators.empty() &&
             precedence(operators.top()) >= precedence(expression[i]))
        values.push(applyOperator_util(values, operators));
      operators.push(expression[i]);
    }
  }
  while (!operators.empty()) values.push(applyOperator_util(values, operators));
  return values.top();
}
