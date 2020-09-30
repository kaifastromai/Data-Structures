#include <iostream>
#include <limits.h>

using namespace std;
class ResizableArray {
private:
  int size;
  int *data;

public:
  ResizableArray(int array_size = 0);
  ~ResizableArray();

  int get(int index);
  void set(int index, int val);
  int get_size();
  void print();

  ResizableArray(ResizableArray &orig);
  void operator=(ResizableArray rhs);

  void resize(int new_size);

  void pop();
  void push_back(int val);
  void insert(int index, int val);
  void remove(int index);
  void push_front(int val);
  bool operator==(ResizableArray &rhs);
  ResizableArray operator+(ResizableArray &rhs);
};
bool operator==(ResizableArray &lhs, ResizableArray &rhs);
ResizableArray operator-(ResizableArray &lhs, ResizableArray &rhs);
//**********************************************
// IMPLEMENTATION
//**********************************************

ResizableArray operator-(ResizableArray &lhs, ResizableArray &rhs) {
  ResizableArray return_ar{lhs.get_size()};
  if (lhs.get_size() != rhs.get_size())
    return return_ar;
  for (int i = 0; i < rhs.get_size(); i++) {
    return_ar.set(i, lhs.get(i) - rhs.get(i));
  }
  return return_ar;
}

ResizableArray ResizableArray::operator+(ResizableArray &rhs) {
  ResizableArray return_ar{this->get_size()};
  if (this->get_size() != rhs.get_size())
    return return_ar;
  for (int i = 0; i < rhs.get_size(); i++) {
    return_ar.set(i, rhs.get(i) + this->get(i));
  }
  return return_ar;
}

ResizableArray::ResizableArray(int array_size) {
  if (array_size <= 0) {
    size = 0;
    data = nullptr;
  } else {
    size = array_size;
    data = new int[size];
    for (int i = 0; i < size; i++)
      set(i, 0);
  }
}
ResizableArray::~ResizableArray() {
  delete[] data;
  size = 0;
}
///////////////////////////////////////////////////
int ResizableArray::get(int index) {
  if (0 <= index && index < size)
    return data[index];
  return INT_MIN; // returns INT_MIN if index out of bounds
}
void ResizableArray::set(int index, int val) {
  if (0 <= index && index < size)
    data[index] = val;
}

int ResizableArray::get_size() { return size; }
void ResizableArray::print() {
  cout << "[";
  for (int i = 0; i < size; i++) {
    string r = (i > size - 2) ? "" : ", ";
    cout << get(i) << r;
  }
  cout << "]\n";
}
////////////////////////////////////////////////////
ResizableArray::ResizableArray(ResizableArray &orig) {
  size = orig.size;
  data = new int[size];
  for (int i = 0; i < size; i++)
    set(i, orig.get(i));
}
void ResizableArray::operator=(ResizableArray rhs) // Note Copy Constructor!
{
  size = rhs.size;
  swap(data, rhs.data);

  /*Below is a direct implementation that could replace the 2 lines above
  delete[] data;
  size = rhs.size;
  data = new int[size];
  for(int i = 0; i < size; i++)
                  set(i, rhs.get(i));*/
}

void ResizableArray::resize(int new_size) {
  if (new_size >= 0 && new_size != size) {
    int *ptr = nullptr;
    if (new_size > 0) {
      ptr = new int[new_size];
      for (int i = 0; i < new_size; i++)
        set(i, (i < size) ? get(i) : 0);
    }
    delete[] data;
    data = ptr;
    size = new_size;
  }
}

void ResizableArray::pop() { resize(size - 1); }
void ResizableArray::push_back(int val) {
  resize(size + 1);
  data[size - 1] = val;
}
void ResizableArray::push_front(int val) {
  resize(size + 1);
  for (int i = size - 1; i > 0; i--) {
    set(i, get(i - 1));
  }
  set(0, val);
}
void ResizableArray::insert(int index, int val) {
  if (0 <= index && index < size) {
    resize(size + 1);
    for (int i = size - 1; i > index; i--)
      set(i, get(i - 1));
    set(index, val);

    /*Below is a direct implementation that could replace the 4 lines above
    int * ptr = new int[size + 1];
    for(int i = 0; i < index; i++)
            ptr[i] = data[i];
    ptr[index] = val;
    for(int i = index + 1; i <= size; i++)
            ptr[i] = data[i-1];
    delete[] data;              	         	//Free old memory
    data = ptr;                 	         	//Reset pointer
    size++;  */
  }
}
void ResizableArray::remove(int index) {
  if (0 <= index && index < size) {
    for (int i = index; i < size - 1; i++)
      set(i, get(i + 1));
    resize(size - 1);

    /*Below is a direct implementation that could replace the 3 lines above
    int *p = new int[size - 1];
    for(int i = 0; i < index; i++)
            p[i] = data[i];
    for(int i = index + 1; i < size; i++)
            p[i - 1] = data[i];
    delete[] data;              	         	//Free old memory
    data = p;                   	         	//Reset pointer
    size--;                     	             //Reset size   */
  }
}

bool operator==(ResizableArray &lhs, ResizableArray &rhs) {
  if (lhs.get_size() != rhs.get_size())
    return false; // Size mismatch, so clearly not equal
  // Return true if and only if every element of two arrays are equal
  for (int i = 0; i < lhs.get_size(); i++)
    if (lhs.get(i) != rhs.get(i))
      return false;
  return true;
}

bool ResizableArray::operator==(ResizableArray &rhs) {
  if (this->get_size() != rhs.get_size()) {
    return false;
  }
  for (int i = 0; i < this->get_size(); i++) {
    if (this->get(i) != rhs.get(i))
      return false;
    return true;
  }
}

int main() {

  ResizableArray ra(4);
  ra.print();
}
