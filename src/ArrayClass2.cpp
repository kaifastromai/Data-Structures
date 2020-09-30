// Array Class
#include <iostream>
#include <string>
using namespace std;
// Mostly taken from the notes for ResizableArray

class Array {
  // Arrays will be managed via a front pointer to the start of their memory
  // block, a back pointer one past the last used memory slot (or to front if
  // empty) and a max pointer pointing one past the last slot that can be used
  // before resizing.
private:
  int *front;
  int *back; // Points one past the last used memory slot
  int *max;  // Points one past the last available memory slot
public:
  Array(); // Default constructor sets private members to initial values.
  Array(int init_size); // All elements initialized to zero. Negative & zero
                        // init_size handled.
  ~Array();             // Destructor frees allocated memory
  void exception(
      string error_message); // Called when anything illegal happens.
                             // Appropriate error message sent by calling method
                             // is output and program terminates with exit.
  int get(
      int pos); // Returns value stored at position. Handles illegal positions.
  void set(int pos, int val); // Overwrites data at index pos with new val.
                              // Handles illegal positions.
  void clear();               // Resets array to size zero and frees memory
  int *find(int val);     // Returns a pointer to the position, or back if not
                          // found.
  void append(int value); // Capacity doubles upon increase
  void insert(int *posPtr, int val); // Capacity doubles if increase is needed
  void erase(
      int *posPtr); // Changes size but not capacity. Handles illegal positions.
  void print() {
    for (int *ptr = front; ptr != back; ptr++)
      cout << *ptr << ' ';
    cout << endl;
  }
};

Array::Array(int init_size) {
  if (init_size >= 0 && init_size <= INT16_MAX) {
    front = new int[init_size]{0};
    back = front + init_size;

  } else {
    exception("Invalid Size argument");
    front = nullptr;
    back = nullptr;
  }
}

Array::Array() {
  front = nullptr;
  back = nullptr;
}
Array::~Array() { clear(); }
void Array::clear() {
  back = nullptr;
  delete[] front;
  front = nullptr;
}
int *Array::find(int val) {
  for (int *ptr = 0; ptr != back; ptr++)
    if (*ptr == val)
      return ptr;
  return back;
}

void Array::append(int val) {
  Array *ptr = this;
  int size = back - front;
  if (max == back) {
    int capacity = max - front;
    int *ptr = nullptr;
    ptr = new int[size * 2];
    for (int i = 0; i < size * 2; i++)
      set(i, (i < capacity) ? get(i) : 0);
    delete[] front;
    front = ptr;
    max = front + size * 2;
    back = front + 1;
    set(back - front - 1, val);
  } else if (max > back) {
    front[size - 1] = val;
    size++;
  }
}

int Array::get(int pos) { return front[pos]; }
void Array::set(int pos, int val) {

  if (pos >= 0 && pos < back - front) {
    front[pos] = val;
  } else {
    exception("Invalid position argument");
    return;
  }
}
void Array::insert(int *posPtr, int val) {
  int size = back - front;
  if (posPtr >= front && posPtr < back) {
    if (max == back) {
      int *new_front = new int[size * 2]{0};
      for (int *ptr = front; ptr < posPtr; ptr++)
        new_front[ptr - front] = *ptr;
      new_front[posPtr - front] = val;
      for (int *ptr = posPtr; ptr < back; ptr++) {
        new_front[(ptr - front) + 1] = *ptr;
      }
      delete[] front;
      back = new_front + (back - front + 1);
      max = new_front + size * 2;
      front = new_front;

    } else if (max > back) {
      for (int i = size; i > (posPtr - front); i--)
        set(i, get(i - 1));
      set(posPtr - front, val);
    }
  } else {
    exception("index out of bounds");
  }
}
void Array::erase(int *pos) {
  if (pos >= front && pos < back) {
    back++;
    for (int *ptr = back - 1; ptr >= pos; ptr--) {
      set(ptr - pos, get((ptr - front) - 1));
    }
  } else {
    exception("index out of bounds");
  }
}
void Array::exception(string error_message) {
  cout << error_message << endl;
  exit(0);
}
int main() {

  Array ar(5);
  for (int i = 0; i < 5; i++) {
    ar.set(i, rand() % 5 + 1);
  }
  ar.print();
}
