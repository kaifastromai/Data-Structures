#include "stack_min.cpp"
#include <iostream>
using namespace std;

// assume some stack class that supports the standard equeue/dequeue/peek
// functionality
// Also, this question is quite vague and to my understanding completely
// impractical, and my implementation is grossly inefficient
class quack {
  // this stack holds the data
  min_stack *m_stck;
  min_stack *stck2;
  int size;
  quack() : size{0}, m_stck{new min_stack()}, stck2{nullptr} {}
  void enqueue(int val) {
    m_stck->push(val);
    size++;
  }
  void dequeue() {
    stck2 = new min_stack();
    for (int i = 0; i < size - 1; i++) {

      stck2->push(m_stck->peek);
      m_stck->pop();
    }
    delete m_stck;
    m_stck = stck2;
    delete stck2;
  }

  int peek() {
    int retval = 0;
    stck2 = new min_stack();
    for (int i = 0; i < size; i++) {
      if (i == size - 1) {
        retval = m_stck->peek;
      }
      stck2->push(m_stck->peek);
      m_stck->pop();
    }
    delete m_stck;
    m_stck = stck2;
    delete stck2;
    return retval;
  }
};