#include "vector.h"
#include <iostream>
#include <vector>
using namespace std;
class mClass {
  int i;

public:
  mClass(int _i = 0) { i = _i; }
  mClass(mClass &_mcls) { cout << "Copy constructor called!" << endl; }
};

mClass mfunc(mClass mcls) {

  mClass mcls1 = mcls;
  return mcls1;
}

void print(int *front, int size) {
  cout << "[";
  for (int *ptr = front; ptr != front + size; ptr++) {
    string r = (ptr > front + size - 2) ? "" : ", ";
    cout << *ptr << r;
  }
  cout << "]\n";
}
int main() {

  std::initializer_list<int> l;
}
