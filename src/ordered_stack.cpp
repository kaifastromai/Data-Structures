#include <iostream>
#include <stack>
using namespace std;
// only integer stacks for the sake of simplicity
//This is soooooo inefficient , and there is definately a better way, but...
void order_stack(stack<int> &s) {
  stack<int> tmp_stack = s;
  stack<int> tmp_stack2 = tmp_stack;
  stack<int> new_stack;
  int largest = 0;
  // find smallest
  int size = 0;
  int largest_index = 0;
  while (!tmp_stack.empty()) {
    size++;
    if (tmp_stack.top() > largest) {
      largest = tmp_stack.top();
      largest_index = size - 1;
    }
    tmp_stack.pop();
  }
  new_stack.push(largest);

  // construct new array without the previous largest element

  for (int i = 0; i < size - 1; i++) {
    largest = 0;
    stack<int> n_tmp_stack = tmp_stack2;
    for (int j = 0; j < size - i; j++) {
      if (j != largest_index) {
        tmp_stack.push(n_tmp_stack.top());
        n_tmp_stack.pop();
      } else if (j == largest_index) {
        n_tmp_stack.pop();
      }
    }
    tmp_stack2 = tmp_stack;

    int n_size = 0;
    while (!tmp_stack.empty()) {
      n_size++;
      if (tmp_stack.top() > largest) {
        largest = tmp_stack.top();
        largest_index = n_size - 1;
      }
      tmp_stack.pop();
    }
    new_stack.push(largest);
  }
  s = new_stack;
}
int main() {

  stack<int> stk;
  for (int i = 0; i < 8; i++) {
    stk.push(rand() % 10 + 1);
  }
  stack<int> tmp_stk = stk;

  cout << "Before ordering " << endl;
  for (size_t i = 0; i < 8; i++) {
    cout << tmp_stk.top() << " ";
    tmp_stk.pop();
  }
  cout << endl;
  tmp_stk = stk;
  order_stack(tmp_stk);
  cout << "Afterward " << endl;
  for (size_t i = 0; i < 8; i++) {
    cout << tmp_stk.top() << " ";
    tmp_stk.pop();
  }
  cout << endl;
}
