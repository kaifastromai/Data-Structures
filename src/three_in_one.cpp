#include <iostream>

class thrine {

  // I assume you a mean a raw array? As opposed to a vector class?
  // Further, considering the lack of elaboration, I will implement only the
  // barest requirements for stack: push, pop, and peak
  // For the sake of facility, the underlying array will be of a fixed size of
  // 100
  struct stack {
  public:
    int begin;
    int end;
    thrine *thr;

  public:
    void push(int item) { thr->push(item, *this); }
    int peak() { return thr->ar[end]; }
    void pop() {
      if (begin != end) {
        end--;
      }
    }
  };
  int ar[100];
  // variables
public:
  stack s1;
  stack s2;
  stack s3;
  void print() {
    std::cout << "Stack1: ";
    for (size_t i = s1.begin; i < s1.end; i++) {
      std::cout << ar[0 + i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Stack2: ";
    for (size_t i = s2.begin; i < s2.end; i++) {
      std::cout << ar[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Stack3: ";
    for (size_t i = s3.begin; i < s3.end; i++) {
      std::cout << ar[i] << ", ";
    }
    std::cout << std::endl;
  }

private:
  void push(int item, stack &stck) {
    if (&s1 == &stck) {
      if (s1.end == s2.begin) {
        shift_forward(s2);
      }
      ar[s1.end] = item;
      s1.end++;
    } else if (&s2 == &stck) {
      if (s2.end == s3.begin) {
        if (!shift_forward(s3)) {
          return;
        }
      }
      ar[s2.end] = item;
      s2.end++;
    } else if (&s3 == &stck) {
      if (s3.end == 100) {
        return;
      }
      ar[s3.end] = item;
      s3.end++;
    }
  }
  bool shift_forward(stack &stck) {
    if (&s2 == &stck) {
      if (stck.end != s3.begin) {
        for (size_t i = 0; i < stck.end - stck.begin; i++) {

          ar[stck.begin + i + 1] = ar[stck.begin + i];
        }
      } else if (stck.end == s2.begin) {

        if (shift_forward(s3)) {
          s2.begin += 2;
          return true;
        }
      }
    } else if (&s3 == &stck) {
      if (s3.end == 100) {
        return false;
      } else {
        for (size_t i = 0; i < stck.end - stck.begin; i++) {
          ar[stck.begin + i + 1] = ar[stck.begin + i];
        }
        s3.begin += 2;
      }
    }
    return true;
  }

  // initial size of each stack
  // methods
public:
  thrine() {
    s1.thr = s2.thr = s3.thr = this;
    s1.begin = 0;
    s1.end = 0;
    s2.begin = 1;
    s2.end = 1;
    s3.begin = 2;
    s3.end = 2;
  }
};

int main() {
  thrine thr;
  thr.s1.push(4);
  thr.s1.push(5);
  thr.s2.push(5);
  thr.s3.push(7);
  thr.s3.push(9);

  thr.print();
}