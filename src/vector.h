#pragma once
#include <initializer_list>
#include <iostream>
namespace csl {
template <class T>

class vector {
private:
  size_t _capacity;
  size_t _size;
  T *front;
  void r_shift(int start_pos) {
    for (int i = _size; i > 0; i++) {
    }
  }

public:
  // default constructor
  vector(size_t _s = 0) {
    if (_s > 0) {
      _capacity = _s;
      _size = _s;
      front = new T[_size];
    } else if (_s == 0) {
      _capacity = 0;
      _size = 0;
      front = nullptr;
    }
  }
  // initializer list constructor
  vector(std::initializer_list<T> l) {
    _size = _capacity = l.size();
    front = new T[_size];
    for (size_t i = 0; i < _size; i++) {
      front[i] = *(l.begin() + i);
    }
  }

  // destructor
  ~vector() {
    // std::cout << "Deleted vector\n";
    delete[] front;
    _capacity = 0;
    _size = 0;
  }
  // copy constructor
  vector(const vector &other)
      : _capacity{other._capacity}, _size{other._size},
        front(new T[other._size]) {
    // copy all of the data from the lvalue to this one
    std::copy(other.front, other.front + other._size, front);
    // std::cout << "Copy constructor called\n";
  }
  // overload copy assignment operator, return a value to self to allow chaining
  // assignments
  vector &operator=(vector &rhs) {
    // std::cout << "Assignment operator called\n";
    if (this != &rhs) {
      _size = rhs._size;
      std::swap(front, rhs.front);
    }
    return *this;
  }
  // move constructor for when we pass rvalues that we don't need to copy
  vector(vector &&rval) : _size{0}, front{nullptr}, _capacity{0} {
    front = rval.front;
    _size = rval._size;
    _capacity = rval._capacity;
    rval.front = nullptr;
    rval._capacity = 0;
    rval._size = 0;
  }

  // create move assignment operator
  vector &operator=(vector &&rval) {
    if (this != &rval) {
      delete[] front;
      _size = rval._size;
      _capacity = rval._capacity;
      front = rval.front;
      rval._capacity = 0;
      rval._size = 0;
      rval.front = nullptr;
    }
    return *this;
  }
  // change size of container to new size
  void resize(size_t new_size, T val = 0) {
    // If the new_size is less than or equal to capacity, we don't do anything
    // because we already have enough memory
    if (new_size > _capacity) {

      T *ptr = new T[new_size];
      for (size_t i = 0; i < new_size; i++) {
        ptr[i] = (i < _size) ? front[i] : val;
      }

      delete[] front;
      front = ptr;
      _size = new_size;
      ptr = nullptr;
    }
  }
  // Replaces values of the container with *val* *count* times, overwriting
  // previous data.
  void assign(size_t count, const T &val) {
    // if the new count is too much smaller than or greater than our capacity,
    // we reallocate memory
    if (_capacity > 3 * count || _capacity < count) {
      delete[] front;
      front = new T[count]{val};
    }
    // else if the count isn't too different from capacity, we maintain our
    // capacity, but change the size; avoiding the reallocation
    else if (_capacity <= 3 * count && _capacity >= count) {
      _size = count;
      int i = 0;
      for (; i < count; i++) {
        front[i] = val;
      }
    }
  }
  // Sets this vector to the range from first to last, assuming that these
  // pointers point to the same type.
  void assign(T *first, T *last) {
    // if the new count is too much smaller than or greater than our capacity,
    // we reallocate memory
    _size = last - first;
    if (_capacity > 3 * _size || _capacity < _size) {
      _capacity = _size;
      delete[] front;
      front = new T[_capacity]{0};
      // std::cout<<" at line:  "<<__LINE__<<" We are reallocating because count
      // is either too small or bigger than capacity\n";
    }

    // else we simply replace the values in the array.
    for (T *ptr = first; ptr != last; ptr++) {
      front[ptr - first] = *ptr;
    }
  }
  void assign(std::initializer_list<T> ilist) {
    _size = ilist.size();
    // if the new count is too much smaller than or greater than our capacity,
    // we reallocate memory
    if (_capacity > 3 * _size || _capacity < _size) {
      _capacity = _size;
      delete[] front;
      front = new T[_size];
    }
    for (size_t i = 0; i < _size; i++) {
      front[i] = *(ilist.begin() + i);
    }
  }
  // insert val into pos
  T *insert(const T *pos, const T &val) {
    if (_capacity == _size && _size > 0) {
      _capacity *= 2;
      _size++;
      resize(_capacity);
      T *ptr = front + _size;
      for (; ptr > pos; ptr--) {
        *ptr = *(ptr - 1);
      }
      *ptr = val;

    } else if (_capacity > _size) {
      _size++;
      T *ptr = front + _size;
      for (; ptr > pos; ptr--) {
        *ptr = *(ptr - 1);
      }
      *ptr = val;
    }
  }
  // 		T* insert(const T* pos, const T&& val) {
  // 			if (_capacity == _size && _size > 0) {
  // 				_capacity *= 2;
  // 				_size++;
  // 				resize(_capacity);
  // 				T* ptr = front + _size;
  // 				for (; ptr > pos; ptr--) {
  // 					*ptr = *(ptr - 1);
  // 				}
  // 				*ptr = val;
  //
  //
  // 			}
  // 			else if (_capacity > _size) {
  //
  // 			}
  // 		}
  void insert(const T *pos, size_t count, const T &val) {

    if (_capacity < _size + count) {
      _size += count;
      _capacity = _size * 2;
      resize(_capacity);
      T *ptr = front + _size - 1;
      for (; ptr > pos + count - 1; ptr--) {
        *ptr = *(ptr - count);
        *(ptr - count) = val;
      }
    } else if (_capacity >= _size + count) {
      T *ptr = front + _size;
      for (; ptr > pos + count - 1; ptr--) {
        *ptr = *(ptr - count);
        *(ptr - count) = val;
      }
    }
  }

  void insert(const T *pos, T *first, T *last) {}
  T *insert(const T *pos, std::initializer_list<T> ilist) {}
  // return pointer to start of container
  T *begin() const { return front; }
  // return pointer to end of container
  T *end() const { return front + _size; }
  // return const pointer to beginning
  const T *cbegin() const { return front; }
  // return const pointer to end
  const T *cend() const { return front + _size; }
  // return size
  size_t get_size() const { return _size; }
  // return maximum size, which most often is the maximum size of the index
  size_t max_size() { return UINTMAX_MAX; }

  // return capacity
  size_t get_capacity() { return _capacity; }
  vector &at(size_t n) {
    try {
      if (n >= _size) {
        throw std::out_of_range("N is out of bounds");
      }

    } catch (const std::invalid_argument &e) {
      // std::cout << e.what() << std::endl;
    }
  }

  // test whether vector is empty
  bool empty() const noexcept {
    if (front == nullptr) {
      return true;
    }
    return false;
  }
  // shrink container to actual elements
  void shrink_to_fit();
  // returns true if all pairwise comparisons are equal
  bool operator==(const vector &rhs) {
    if (_size == rhs._size) {
      for (size_t i = 0; i < _size; i++) {
        if (front[i] != rhs.front[i]) {
          return false;
        }
      }
      return true;
    } else
      return false;
  }
  // returns opposite of ==
  bool operator!=(const vector &rhs) { return !(*this == rhs); }
};

}; // namespace csl
