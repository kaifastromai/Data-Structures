// Intro Lecture to Linked Lists
#include <iostream>
#include <string>
using namespace std;

struct Node {
  int info;
  Node *next;
};

void push_front(Node *&theHead, int val) { theHead = new Node{val, theHead}; }
void print(Node *head) {
  for (Node *ptr = head; ptr != nullptr; ptr = ptr->next)
    cout << ptr->info << endl;
}
void push_back(Node *head, int val) {
  if (head == nullptr) {
    push_front(head, val);
  } else {
    Node *ptr = head;
    while (ptr->next != nullptr) {

      ptr = ptr->next;
    }
    ptr->next = new Node{val, nullptr};
  }
}

int main() {
  Node *head = new Node{9, nullptr};

  for (int val = 8; val >= 1; val--) {
    push_front(head, val);
  }
  push_back(head, 10);
  print(head);
}