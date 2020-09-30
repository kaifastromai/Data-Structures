#include <iostream>
// doubly linked list
using namespace std;

struct Node {
  int info;
  Node *prev;
  Node *next;
};
class List {
private:
  Node *head; // Points to first Node, or nullptr
  Node *tail;

public:
  List(int init_size = 0); // Also default constructor
  ~List();                 // Destructor

  List(const List &orig);   // Copy Constructor
  void operator=(List rhs); // Copy Assignment Operator

  int get(int index);
  void set(int index, int value);
  void push_front(int value);
  void push_back(int value);
  void pop_front();
  void pop_back();
  void print();
  int size();
  void insert(int index, int value);
  void remove(int index);
  bool operator==(List &rhs);
  bool operator!=(List &rhs);
};
///////////////////////////////////////////////////////////////
//				IMPLEMENTATION
///////////////////////////////////////////////////////////////////////
List::List(int init_size) // Default parameter value not repeated here
{
  tail = new Node{0, nullptr, nullptr};
  head = tail;
  // Whenever init_size is not positive
  for (int i = 0; i < init_size; i++)
    push_front(0); // Initialized with all zeros
}

List::~List() {
  while (head != nullptr)
    pop_front();
}
void List::push_front(int value) {
  // First construct a new Node
  Node *new_head = new Node{value, nullptr, head};
  head->prev = new_head;
  head = new_head; // Then set head to point to the new Node
}
void List::pop_front() {
  if (head != tail) {
    Node *new_head = head->next;
    delete head;
    head = new_head;
    new_head->prev = nullptr;
  }
}
void List::print() { // This idiom iterates through each node
  for (Node *ptr = head; ptr != tail; ptr = ptr->next) {
    cout << ptr->info << ' ';
  }
  cout << " ****** ";
  for (Node *ptr = tail->prev; ptr != nullptr; ptr = ptr->prev) {
    cout << ptr->info << ' ';
  }
  cout << endl;
}
int List::size() {
  int sz = 0;
  // This idiom iterates through each node
  for (Node *ptr = head; ptr != tail; ptr = ptr->next)
    sz++;
  return sz;
}
List::List(const List &orig) : tail{new Node{0, nullptr, nullptr}}, head(tail) {
  for (Node *ptr = orig.head; ptr != orig.tail; ptr = ptr->next) {
    push_back(ptr->info); // TODO: Inefficient -- List re-traversed every time!
  }
}

// Improved copy constructor
/*
List::List(const List& orig)
{
        if (orig.head == nullptr)	//In case List to copy is empty
                head = nullptr;
        else {
                Node* ptr1 = head = new Node{ orig.head->info, nullptr };
//Create head Node

  //Iterate through existing List with ptr2, copying Node by Node with ptr1
                for (Node* ptr2 = orig.head->next; ptr2 != nullptr; ptr2 =
ptr2->next) ptr1 = ptr1->next = new Node{ ptr2->info, nullptr };
        }
}
*/
void List::push_back(int value) {
  if (head == tail)
    push_front(value);
  else {
    // last_ptr now points to the last Node
    tail->prev->next = new Node{value, tail->prev, tail};
    tail->prev = tail->prev->next;
  }
}
int main() {

  List L;
  for (int i = 4; i >= 0; i--) {
    L.push_back(i);
  }
}

