#include <iostream>
#include <limits>
using namespace std;
struct Node {
  int info;
  Node *next;
};
class List {
private:
  Node *head; // Points to first Node, or nullptr
public:
  List(int init_size = 0); // Also default constructor due to default parameter
  ~List();

  List(const List &orig);
  List(List &&orig) {
    head = nullptr;
    swap(head, orig.head);
    cout << "Called move constructor" << endl;
  }
  List &operator=(List &&orig) {
    head = nullptr;
    swap(head, orig.head);
    cout << "Called move assignment operator" << endl;

    return *this;
  }

  void operator=(List &rhs);

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
  void erase_after(Node *ptr);
  bool operator==(List &rhs);
};
List::List(int init_size) // Default parameter value not repeated here
{
  head = nullptr; // Whenever init_size is not positive
  for (int i = 0; i < init_size; i++)
    push_front(0); // Initialized with all zeros
  cout << "Default construcot" << endl;
}
List::~List() {
  while (head != nullptr)
    pop_front();
  cout << "Called destructor" << endl;
}
// Easy-to-code copy constructor
/*
List::List(const List& orig)
{
        head = nullptr;
        for (Node* ptr = orig.head; ptr != nullptr; ptr = ptr->next)
        {
                push_back(ptr->info);	//TODO: Inefficient -- List re-traversed
every time!
        }
}*/

// Improved copy constructor
List::List(const List &orig) {
  if (orig.head == nullptr) // In case List to copy is empty
    head = nullptr;
  else {
    Node *ptr1 = head = new Node{orig.head->info, nullptr}; // Create head Node

    // Iterate through existing List with ptr2, copying Node by Node with ptr1
    for (Node *ptr2 = orig.head->next; ptr2 != nullptr; ptr2 = ptr2->next)
      ptr1 = ptr1->next = new Node{ptr2->info, nullptr};
  }
  cout << "Called copy constructor" << endl;
}

void List::operator=(List &rhs) {
  cout << "called assignment operator" << endl;

  swap(head, rhs.head);
}
int List::get(int index) {
  if (index < 0 || index >= size()) {
    return INTMAX_MIN; // The idea is that we signal that an exception occurred.
  }
  // This idiom finds the Node at an index
  Node *ptr = head;
  for (int i = 0; i < index; i++)
    ptr = ptr->next;

  return ptr->info;
}

void List::set(int index, int value) {
  if (0 <= index && index < size()) {
    // This idiom finds the Node at an index
    Node *ptr = head;
    for (int i = 0; i < index; i++)
      ptr = ptr->next;

    ptr->info = value;
  }
}
void List::push_front(int value) {
  // First construct a new Node
  Node *new_head = new Node;
  new_head->info = value;
  new_head->next = head;

  head = new_head; // Then set head to point to the new Node
  // Alternative: head = new Node{value, head};
}
void List::push_back(int value) {
  if (head == nullptr)
    push_front(value);
  else {
    // This idiom locates the last Node
    Node *last_ptr = head;
    while (last_ptr->next != nullptr)
      last_ptr = last_ptr->next;

    // last_ptr now points to the last Node
    last_ptr->next = new Node;
    last_ptr = last_ptr->next;
    last_ptr->info = value;
    last_ptr->next = nullptr;
    // Alternative: last_ptr->next = new Node{ value, nullptr };
  }
}
void List::pop_front() {
  if (head != nullptr) {
    Node *new_head = head->next;
    delete head;
    head = new_head;
  }
}
void List::pop_back() {
  if (head != nullptr) // No Node case
  {
    if (head->next == nullptr) // Single Node case
    {
      pop_front();
    } else {
      // Locate the Node before the last Node (penultimate Node)
      Node *pen_ptr = head;
      while (pen_ptr->next->next != nullptr)
        pen_ptr = pen_ptr->next;

      delete pen_ptr->next;
      pen_ptr->next = nullptr;
    }
  }
}

void List::print() { // This idiom iterates through each node
  for (Node *ptr = head; ptr != nullptr; ptr = ptr->next) {
    cout << ptr->info << ' ';
  }
  cout << endl;
}
int List::size() {
  int sz = 0;
  // This idiom iterates through each node
  for (Node *ptr = head; ptr != nullptr; ptr = ptr->next)
    sz++;
  return sz;
}
void List::insert(int index, int value) {
  if (head == nullptr || index < 0 || index >= size())
    return;
  if (index == 0)
    push_front(value);
  else {
    // This idiom finds the Node at index - 1
    Node *ptr = head;
    for (int i = 0; i < index - 1; i++)
      ptr = ptr->next;

    Node *insert_node = new Node;
    insert_node->info = value;
    insert_node->next = ptr->next;
    ptr->next = insert_node;
  }
}
void List::remove(int index) {
  if (head == nullptr || index < 0 || index >= size())
    return;
  if (index == 0)
    pop_front();
  else {
    // This idiom finds the Node at index - 1
    Node *ptr = head;
    for (int i = 0; i < index - 1; i++)
      ptr = ptr->next;

    Node *next_node = ptr->next->next;
    delete ptr->next;
    ptr->next = next_node;
  }
}
void List::erase_after(Node *ptr) {
  if (head == nullptr || ptr == nullptr)
    return;
  if (ptr == head) {
    pop_front();
  }

  Node *ptr_track = head;
  while (ptr_track->next != ptr) {
    ptr_track = ptr_track->next;
  }

  Node *next_node = ptr_track->next->next;
  delete ptr_track->next;
  ptr_track->next = next_node;
}
bool List::operator==(List &rhs) {
  if (size() != rhs.size()) {
    return false;
  }
  Node *ptr1 = head;
  Node *ptr2 = rhs.head;
  while (ptr1 != nullptr) {
    if (ptr1->info != ptr2->info)
      return false;
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }
  return true;
}

////////////////////////////////////////////
int main() {
  List l;
  for (size_t i = 0; i < 4; i++) {
    l.push_front(i);
  }

  l.print();
}