#include <iostream>
using namespace std;
int integer_sums(int n) {
  if (n > 0) {
    if (n == 1) {
      return 1;
    }
    return integer_sums(n - 1) + 1;
  } else {
    return 1;
  }
}

int powers(int n) {
  if (n > 0) {
    if (n == 1) {
      return 2;
    }
    return 2 * powers(n - 1);
  }
}
int factorial(int n) {
  if (n > 0) {
    if (n == 1) {
      return 1;
    }
    return n * factorial(n - 1);
  }
}
int f(int n) {
  if (n > 0) {
    if (n == 1) {
      return 1;
    } else if (n == 2) {
      return 1;
    } else {
      return f(n - 1) + 2 * f(n - 2);
    }
  }
}
void print_subset_sum(int a[], int size, int sum = 0) {
  if (size == 0) {
    cout << sum << " ";
    return;
  }
  print_subset_sum(a, size - 1, sum + a[size - 1]);
  print_subset_sum(a, size - 1, sum);
}
int main() {
  int a[] = {1, 2, 5};
  print_subset_sum(a, 3);
}
