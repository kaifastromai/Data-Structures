#include <iostream>
using namespace std;
class stack_set {
  struct Node {
    int data;
    int set;
    Node *next;
  };
  // after any one stack suppercedes this size, a new stack is initiliazed
  int capacity = 20;
  // for the sake of simplicity, this array will be of a constant size, but this
  // could be changes with relatively little effort and a bit of time

  Node *nodes[20]{nullptr};
  int current_node = 0;
  int current_size = 0;

public:
  void push(int val) {
    if (current_size >= 20) {
      current_node++;
      current_size = 0;
    }
    nodes[current_node] = new Node{val, current_node, nodes[current_node]};
    current_size++;
  }
  void pop() {
    if (nodes[current_node] != nullptr) {

      Node *to_delete = nodes[current_node];
      nodes[current_node] = nodes[current_node]->next;
      delete to_delete;
      if (current_node != 0 && --current_size == 0) {
        current_node--;
        current_size = 20;
      }
    }
  }
  void print() {
    for (size_t i = 0; i < 20; i++) {
      for (Node *nptr = nodes[i]; nptr != nullptr; nptr = nptr->next) {
        cout << "Set: " << nptr->set << " " << nptr->data << endl;
      }
    }
  }
};

int main() {


  stack_set ss;
  for (int i = 0; i < 40; i++) {
    ss.push(i);
  }

  ss.print();
}