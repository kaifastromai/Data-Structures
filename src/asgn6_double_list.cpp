

#include <iostream>
#include <string>
using namespace std;

struct Node {
  int info;
  Node *prev; // pointer to previous Node or nullptr
  Node *next; // pointer to next Node or the sentinel
};

class List {
private:
  Node *head;     // Points to first Node, or the sentinel if the List is empty
  Node *sentinel; // Points to a special non-data Node at the end

public:
  List(int init_size = 0); // Also default constructor due to default parameter
  List(const List &orig);  // Copy constructor
  ~List();
  void operator=(List rhs);
  void push_front(int value);
  void pop_front();
  void exception(string error_message);

  void push_back(int value);
  void pop_back();
  void print();
  int size();
  bool operator==(List &rhs);

  int get(Node *pos);
  void set(Node *pos, int value);
  void insert(Node *pos, int value);
  void remove(Node *pos);
};

//***********************IMPLEMENTATIONS****************************************
List::List(int init_size) // Default parameter value not repeated here
{
  if (init_size < 0)
    init_size = 0;
  sentinel = new Node{0, nullptr, nullptr};
  head = sentinel;
  for (int i = 0; i < init_size; i++)
    push_front(0); // Initialized with all zeroes
}
List::List(const List &orig) {
  sentinel = new Node{0, nullptr, nullptr};
  head = sentinel;

  for (Node *ptr = orig.head; ptr != orig.sentinel; ptr = ptr->next) {
    push_back(ptr->info);
  }
}
List::~List() {
  while (head != sentinel)
    pop_front();
  delete sentinel;
}
void List::operator=(List rhs) {
  swap(head, rhs.head);
  swap(sentinel, rhs.sentinel);
}
void List::push_front(int value) {
  Node *new_head = new Node{value, nullptr, head};
  head->prev = new_head;
  head = new_head;
}
void List::pop_front() // Do nothing on empty List
{
  if (head != sentinel) {
    Node *new_head = head->next;
    delete head;
    head = new_head;
    head->prev = nullptr;
  }
}
// This is called whenever something "bad" happens and
// we want to gracefully terminate the program.
void List::exception(string error_message) {
  cout << error_message << endl;
  system("pause");
  exit(EXIT_FAILURE);
}

void List::push_back(int value) {
  Node *nn = new Node{value, sentinel, sentinel->prev};
  sentinel->prev = nn;
}

void List::pop_back() {
  if (head != sentinel) // No Node case
  {
    if (head->next == sentinel) // Single Node case
    {
      pop_front();
    } else {
      // Locate the Node before the last Node (penultimate Node)
      auto ptr = sentinel->prev->prev;
      delete sentinel->prev;
      ptr->next = sentinel;
    }
  }
}
void List::print() { // This idiom iterates through each node
  for (Node *ptr = head; ptr != sentinel->prev; ptr = ptr->next) {
    cout << ptr->info << ' ';
  }
  cout << endl;
}
int List::size() {
  int sz = 0;
  // This idiom iterates through each node
  for (Node *itr = head; itr != sentinel->prev; itr = itr->next)
    sz++;
  return sz;
}

bool List::operator==(List &rhs) {
  if (size() != rhs.size()) {
    return false;
  }
  Node *ptr1 = head;
  Node *ptr2 = rhs.head;
  while (ptr1 != sentinel->prev && ptr2 != sentinel->prev) {
    if (ptr1->info != ptr2->info)
      return false;
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }
  return true;
}

int List::get(Node *pos) {
  // The only way to do an error check on the pos pointer would be to iterate
  // through every element in our List and make sure it matches one of them,
  // which is needlessly wasteful and incredibly inefficient, acoordingly, I
  // will assume that *pos* is already sanitized
  return pos->info;
}

void List::set(Node *pos, int val) {
  // same problem as get(), so we assume that the position is already sanitized
  // for usage
  // This idiom finds the Node at an index
  pos->info = val;
}

void List::insert(Node *pos, int value) {
  // assume pos is sanitized
  if (head == nullptr) // empty case
    return;
  if (pos == head)
    push_front(value);
  else {
    pos = new Node{value, pos->prev, pos};
  }
}

void List::remove(Node *pos) {
  if (head == sentinel)
    return;
  if (pos == sentinel)
    pop_front();
  else {
    pos->prev = pos->next;
    pos->next->prev = pos->prev;
    delete pos;
  }
}

int main() {}
