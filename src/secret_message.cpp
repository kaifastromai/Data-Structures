#include <iostream>
using namespace std;
struct Node {
  char info;
  Node *next;
};

// Returns 1 if parentheses in s are balanced, 0 if not
// Assume that s consists entirely of '(' and ')'
int is_balanced(string s) {
  Node *top = nullptr;
  for (size_t i = 0; i < s.length(); i++) {
    if (s[i] == '(') {
      if (top == nullptr) {
        top = new Node{'(', nullptr};

      } else {
        top = new Node{'(', top};
      }
    } else if (s[i] == ')') {
      if (top == nullptr) {
        return 0;
      }
      Node *deleted = top;
      top = top->next;
      delete deleted;
    }
  }
  return (top == nullptr) ? 1 : 0;
}

int main() {
  int N = 40;
  string parens[40] = {
      "()()(())(",   "()()()",       "(()())",     "(()())(())",
      "()()())",     "((()(()))",    "((()()))",   "((()()))()()",
      "(()())(",     "((()()))()()", "(()())()",   "()(())()",
      "(()()))()",   "(()())()()",   "()()())",    "(()()()()",
      "()())))",     "()()(())",     "(((()())))", "(((()()))))",
      "((((()())))", "((()())))(",   "((()()(())", "((()()))(())",
      "(())()())",   "(((()())))",   "(())()()()", "(()()))",
      "(((()()))))", "((((()())))",  "(())()()",   "()()(())",
      "())()()",     "((()()))",     "()(()())",   "((()()))(()",
      "((()()))",    "()(()()",      "((()()))",   "()"};
  // Step through all N strings in parens and print a sequence of N consecutive
  // 1's and 0's according to whether the string is balanced or not.
  for (int i = 0; i < N; i++) {
    cout << is_balanced(parens[i]);
  }
  cout << endl;

  // Interpreted as 5 bytes of ASCII characters, the sequence of 1's and 0's
  // spells a five letter English word. Print out that hidden word.

  cout << "The hidden word is"
       << " stack" << endl;
}
