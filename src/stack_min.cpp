#include <iostream>
using namespace std;
class min_stack {
  struct Node {
    int data;
    Node *next;
  };
  struct Min_Node {
    Node *min;
    Min_Node *next;
  };
  // I'm not entirely certain what you mean by 'minimum element', so I will
  // assume that is the Node with the smallest value for 'data' , as opposed to
  // the value itself
  Node *top;
  Min_Node *min_top;

public:
  min_stack() : top{nullptr} {}
  void push(int val) {
    Node *oldtop = top;
    top = new Node{val, top};
    if (oldtop == nullptr)
      min_top = new Min_Node{top, min_top};
    else {
      if (min_top->min->data > val) {
        min_top = new Min_Node{top, min_top};
      }
    }
  }

  void pop() {
    if (top != nullptr) {
      Node *deleted = top;
      if (top == min_top->min) {
        Min_Node *min_deleted = min_top;
        min_top = min_top->next;
        delete min_deleted;
      }
      top = top->next;
      delete deleted;
    }
  }
  int peek() { return top->data; }

  Node min() { return *min_top->min; }
};

int main() {
  min_stack ms;
  ms.push(0);
  ms.push(5);
  ms.push(3);
  ms.push(9);
  ms.push(-1);

  cout << ms.min().data << endl;
}