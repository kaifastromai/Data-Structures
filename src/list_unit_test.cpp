#include "linked_list.h"

int main() {
  cout << "Testing default initializer with argument 5 (Should be 5 zeros) and "
          "print function: "
       << endl;
  List l(5);
  l.print();
  List l2(4);
  List n_list(static_cast<List &&>(l2));
  l = std::move(l2);
}

