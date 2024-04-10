#include <iostream>
#include <stack>

using namespace std;

bool checkParentheses(const string &text);

int main() {
  string test1 = "(()(()()))";   // the correct parentheses notation
  string test2 = "())(()(()))";  // wrong parentheses notation
  cout << "Test #1 : " << test1 << " : " << boolalpha << checkParentheses(test1)
       << endl;
  cout << "Test #2 : " << test2 << " : " << boolalpha << checkParentheses(test2)
       << endl;
  return 0;
}

bool checkParentheses(const string &text) {
  stack<char> s;
  for (char c : text) {
    if (!s.empty() && s.top() == '(' && c == ')')
      s.pop();
    else
      s.push(c);
  }
  return s.empty();
}
