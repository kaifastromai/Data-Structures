// Templated Queue
#include <iostream>
#include <string>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
template <typename T> struct Queue {
  struct Node {
    T data;
    Node *next;
    Node(T val) {
      data = val;
      next = NULL;
    } // Node's default constructor
  };

  Node *first; // Pointer to the front of the queue
  Node *last;  // Pointer to the back of the queue

  Queue() { first = last = nullptr; } // Default constructor for an empty stack
  ~Queue() {
    while (first != last) {
      remove();
    }
  }                          // Destructor
  Queue(const Queue &orig);  // Copy constructor
  void operator=(Queue rhs); // Assignment operator

  // Queue methods:
  void add(T item) {
    if (last == first) {
      first = new Node{item, last};
    }
    Node n_last = new Node{item, nullptr};
    last->next = n_last;
    last = n_last;
  }
  T remove() {
    if (front->next != nullptr) {
      Node n_first = front->next;
      delete first;
      front = n_first;
    } else {
      Exception("The queue is empty...");
    }
  }
  T peek() { return *first; }
  bool is_empty() { return first == last; }

  bool operator==(const Queue<T> &rhs) {
    Node *ptr_rhs = rhs.first;
    for (Node *ptr = first; ptr != nullptr; ptr = ptr->next) {
      if (*ptr->data != *ptr_rhs->data) {
        return false;
      }
      ptr_rhs = ptr_rhs->next;
    }
  }
  bool operator!=(const Queue<T> &rhs) { return !(*this == rhs); }

  void print()
      ///////////////////////////////////
      // Queue<T> Implementation
      // Implement all the methods of Queue<T>
      ///////////////////////////////////
      template <typename T>
      void Queue<T>::print() {
    if (is_empty()) {
      cout << "Queue is empty\n";
    } else {
      cout << "Queue front: ( ";
      for (Node *ptr = first; ptr != NULL; ptr = ptr->next) {
        cout << ptr->data << ' ';
      }
      cout << ')' << endl;
    }
  }
  template <typename T> void Queue<T>::Exception(std::string message) {
    std::cout << "Exception: " << message << std::endl;
    system("pause");
    exit(0);
  }
  ////////////////////////////
  template <typename T>
  Queue<T> QueueCopyTester(
      Queue<T> s) // See if copy construction and assignment are correct
  {
    Queue<T> t;
    t = s;
    return t;
  }

  int main() {
    Queue<int> q;
    q.add(7);
    cout << "Queue Copy/Assignment "
         << (q == QueueCopyTester(q) ? "successful\n" : "failed\n");
    q.remove();

    while (true) {
      q.print();
      cout << "1 add - item\n";
      cout << "2 remove\n";
      cout << "3 peek\n";
      cout << "4 is_empty()\n";
      cout << "Other to Quit\n";
      int input;
      cin >> input;
      if (input == 1) {
        int item;
        cin >> item;
        q.add(item);
      } else if (input == 2) {
        cout << "remove = " << q.remove() << endl;
      } else if (input == 3) {
        cout << "peek = " << q.peek() << endl;
      } else if (input == 4) {

        cout << (q.is_empty() ? "Queue is empty\n" : "Queue is not empty\n");
      } else
        break;
      cout << endl;
    }

    system("pause");
    return 0;
  }