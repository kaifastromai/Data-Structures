// Array Class
#include <iostream>
#include <string>
using namespace std;

class Array {
  // Arrays will be managed via a pointer to the start of their memory block,
  // a size parameter for the number of slots actually used
  // and a capacity for the number of slots that can be used before resizing.
private:
  int *front;
  int size;
  int capacity;

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
  void set(int pos, int val);    // Overwrites data at index pos with new val.
                                 // Handles illegal positions.
  void clear();                  // Resets array to size zero and frees memory
  int find(int val);             // Returns index of first, or size if not found
  void append(int value);        // Capacity doubles upon increase
  void insert(int pos, int val); // Capacity doubles if increase is needed
  void
  erase(int pos); // Changes size but not capacity. Handles illegal positions.
};

Array::Array(int init_size) {
  if (init_size >= 0 && init_size <= INT16_MAX) {
    size = init_size;
    capacity = size;
    front = new int[size]{0};
  } else {
    exception("Invalid Size argument");
    front = nullptr;
    size = capacity = 0;
  }
}

Array::Array() {
  front = nullptr;
  size = capacity = 0;
}
Array::~Array() { clear(); }
void Array::clear() {
  size = capacity = 0;
  delete[] front;
  front = nullptr;
}
int Array::find(int val) {
  for (int i = 0; i < size; i++)
    if (front[i] == val)
      return i;
  return size;
}

void Array::append(int val) {
  if (capacity == size) {

    int *ptr = nullptr;
    ptr = new int[size * 2];
    for (int i = 0; i < size * 2; i++)
      set(i, (i < capacity) ? get(i) : 0);
    delete[] front;
    front = ptr;
    capacity = size * 2;
    size++;
    set(size - 1, val);
  } else if (capacity > size) {
    front[size - 1] = val;
    size++;
  }
}
// Mostly taken from the notes for ResizableArray
int Array::get(int pos) { return front[pos]; }
void Array::set(int pos, int val) {

  if (pos >= 0 && pos < size) {
    front[pos] = val;
  } else {
    exception("Invalid position argument");
    return;
  }
}
void Array::insert(int index, int val) {
  if (index >= 0 && index < size) {
    if (capacity == size) {
      int *new_front = new int[size * 2]{0};
      for (int i = 0; i < index; i++)
        new_front[i] = front[i];
      new_front[index] = val;
      for (int i = index; i < size; i++) {
        new_front[i + 1] = front[i];
      }
      delete[] front;
      front = new_front;
      size++;
      capacity = size * 2;

    } else if (capacity > size) {
      for (int i = size; i > index; i--)
        set(i, get(i - 1));
      set(index, val);
    }
  } else {
    exception("index out of bounds");
  }
}
void Array::erase(int pos) {
  if (pos >= 0 && pos < size) {
    size--;
    for (int i = size - 1; i >= pos; i--) {
      set(i, get(size - 1));
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
}
