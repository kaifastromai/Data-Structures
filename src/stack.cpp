#include <iostream>
#include <list>
using namespace std;
struct Stack {
  struct Node // Node built into stack specification
  {
    int val;
    Node *next;
    Node(int item = 0, Node *next = nullptr) {
      val = item;
      this->next = next;
    }
  };

  Node *top; // Pointer to top of the stack

  Stack();                   // Default constructor for an empty stack
  ~Stack();                  // Destructor
  Stack(const Stack &orig);  // Copy constructor
  void operator=(Stack rhs); // Assignment operator
  // Stack methods:
  void push(int item);
  int pop();
  int peek();
  bool is_empty();
  void print();
  bool operator<(Stack &other);
};
bool operator==(const Stack &lhs, const Stack &rhs);
bool operator!=(const Stack &lhs, const Stack &rhs);
bool Stack::operator<(Stack &other) {
  Stack::Node *ptr1 = top;
  Stack::Node *ptr2 = other.top;
  while (true) {
    if (ptr1 == nullptr && ptr2 == nullptr) {
      return false;
    }
    if (ptr1->val < ptr2->val)
      return true;
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }
}

Stack::Stack() { top = nullptr; }
Stack::~Stack() {
  while (top != nullptr)
    pop();
}
Stack::Stack(const Stack &orig) {
  if (orig.top == nullptr) // In case Stack to copy is empty
    top = nullptr;
  else {
    Node *ptr1 = top = new Node{orig.top->val, nullptr}; // Create top Node

    // Iterate through existing Stack with ptr2, copying Node by Node with ptr1
    for (Node *ptr2 = orig.top->next; ptr2 != nullptr; ptr2 = ptr2->next)
      ptr1 = ptr1->next = new Node{ptr2->val, nullptr};
  }
}
void Stack::operator=(Stack rhs) { swap(top, rhs.top); }
void Stack::push(int item) { top = new Node(item, top); }
int Stack::pop() {
  int return_val = peek();
  if (top != nullptr) {
    Node *delete_node = top;
    top = top->next;
    delete delete_node;
  }
  return return_val;
}

int Stack::peek() {
  if (top == nullptr)
    return -1; // Must return something
  else
    return top->val;
}
void Stack::print() {
  if (top == nullptr) {
    cout << "Stack is empty\n";
    return;
  }
  cout << "Stack: ";
  Node *ptr = top;
  while (ptr != nullptr) {
    cout << ptr->val << ' ';
    ptr = ptr->next;
  }
  cout << endl;
}
bool operator==(const Stack &lhs, const Stack &rhs) {
  Stack::Node *ptr1 = lhs.top;
  Stack::Node *ptr2 = rhs.top;
  while (true) {
    if (ptr1 == nullptr && ptr2 == nullptr)
      return true;
    if (ptr1 == nullptr && ptr2 != nullptr ||
        ptr1 != nullptr && ptr2 == nullptr)
      return false;
    if (ptr1->val != ptr2->val)
      return false;
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }
}
bool operator!=(const Stack &lhs, const Stack &rhs) {
  return !(lhs == rhs); // Alternatively, !operator==(lhs,rhs)
}

class EasyListStack {
  list<int> l;

  void push(int item) { l.push_back(item); }
  int pop() {
    int return_val = peek();
    l.pop_back();
    return return_val;
  }
  int peek() { return l.back(); }
  bool is_empty() { return l.empty(); }
};