// Working with Raw Arrays and Functions in two implementations

/*IMPORTANT
Work exclusively with one of the two array implementations.
Functions that change the size don't update the back pointer,
and functions that change the back pointer don't update the size.*/

#include <algorithm>
#include <iostream>
#include <time.h>
using namespace std;

void print(int *front, int size)
{
  for (int i = 0; i < size; i++)
    cout << front[i] << ' ';
  cout << endl;
}
void print(int *front, int *back)
{
  for (int *ptr = front; ptr != back; ptr++)
    cout << *ptr << ' ';
  cout << endl;
}
int sum(int *front, int size)
{
  int sum = 0;
  for (int i = 0; i < size; i++)
    sum += front[i];
  return sum;
}
int sum(int *front, int *back)
{
  int sum = 0;
  for (int *ptr = front; ptr != back; ptr++)
    sum += *ptr;
  return sum;
}

bool contains(int *front, int size, int val)
{
  for (int i = 0; i < size; i++)
  {
    if (front[i] == val)
      return true;
  }
  return false;
}
bool contains(int *front, int *back, int val)
{
  for (int *ptr = front; ptr != back; ptr++)
  {
    if (*ptr == val)
      return true;
  }
  return false;
}

int find(int *front, int size, int val)
{
  for (int i = 0; i < size; i++)
    if (front[i] == val)
      return i;
  return size;
}
int *find(int *front, int *back, int val)
{
  for (int *ptr = front; ptr < back; ptr++)
    if (*ptr == val)
      return ptr;
  return back;
}

void append(int *&front, int &size, int val)
{
  int *new_front = new int[size + 1]; // Allocate sufficient memory
  for (int i = 0; i < size; i++)      // Copy old elements over
    new_front[i] = front[i];
  new_front[size] = val;
  delete[] front;
  front = new_front;
  new_front = nullptr;
  size++;
}
void append(int *&front, int *&back, int val)
{
  int *new_front = new int[back - front + 1]; // Allocate sufficient memory
  int *ptr = front, *qtr = new_front;
  while (ptr != back)
    *qtr++ = *ptr++;
  *qtr = val;
  back = new_front + (back - front + 1); // The parenthesis are important!
  delete[] front;
  front = new_front;
}

void insert(int *&front, int &size, int pos, int val)
{
  int *new_front = new int[size + 1];
  for (int i = 0; i < pos; i++)
    new_front[i] = front[i];
  new_front[pos] = val;
  for (int i = pos; i < size; i++)
  {
    new_front[i + 1] = front[i];
  }
  delete[] front;
  front = new_front;
  size++;
}
bool delete_all(int *&front, int *&back, int val)
{
  int index = 0;
  int size = back - front;
  bool success = 0;
  while (index <= size)
  {
    if (index == size)
    {
      success = 0;
      break;
    }
    if (front[index] == val)
    {
      success = 1;
      break;
    }
    index++;
  }

  if (success)
  {
    int *new_front = new int[size - 1];
    int tmp_index = 0;
    for (size_t i = 0; i < size; i++)
    {
      if (i < index)
      {
        new_front[tmp_index] = front[i];
        tmp_index++;
      }
      else if (i > index)
      {
        new_front[tmp_index] = front[i];
        tmp_index++;
      }
      else if (i == index)
      {
      }
    }
    back = new_front + size - 1; // The parenthesis are important!
    delete[] front;
    front = new_front;
    new_front = nullptr;

    cout << "Calling again\n";
    delete_all(front, back, val);
  }
  else
    return false;
  return true;
}

void insert(int *&front, int *&back, int *pos, int val)
{
  int s_it = 0;
  int *new_front = new int[back - front + 1]; // Allocate sufficient memory
  int *ptr = front, *qtr = new_front;
  for (int i = 0; i < back - front + 1; i++)
  {
    if (front + i < pos)
    {
      new_front[i] = front[s_it];
      s_it++;
    }
    else if (front + i > pos)
    {
      new_front[i] = front[s_it];
      s_it++;
    }
    else if (front + i == pos)
      new_front[i] = val;
    else
    {
      cout << "Unhandled error\n";
    }
  }
  cout << "Broke from loop\n";

  back = new_front + (back - front + 1); // The parenthesis are important!
  delete[] front;
  front = new_front;
}
void erase(int *&front, int &size, int pos)
{
  int *new_front = new int[size - 1];

  for (int i = 0; i < pos; i++)
    new_front[i] = front[i];
  for (int i = pos + 1; i < size; i++)
    new_front[i - 1] = front[i];
  delete[] front;
  front = new_front;
  size--;
}
void erase(int *&front, int *&back, int *pos)
{

  int *new_front = new int[back - front - 1];
  for (int *ptr = front; ptr != pos; ptr++)
  {
    new_front[ptr - front] = *ptr;
  }
  for (int *ptr = pos + 1; ptr != back; ptr++)
  {
    new_front[ptr - front - 1] = *ptr;
  }
  back = new_front + (back - front - 1); // The parenthesis are important!
  delete[] front;
  front = new_front;
}
void erase_all(int *&front, int *&back, int val)
{

  for (size_t i = 0; i < back - front; i++)
  {
    if (front[i] == val)
    {
      erase(front, back, front + i);
    }
  }
}

void doubler(int *&front, int *&back)
{
  int index = 0;
  int *new_front = new int[(back - front) * 2];
  for (int i = 0; i < back - front; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      new_front[index] = front[i];
      index++;
    }
  }
  back = new_front + 2 * (back - front); // The parenthesis are important!
  delete[] front;
  front = new_front;
}
void stepwise_increase(int *&front, int *&back)
{
  int index = 0;
  int s = back - front;
  int *new_front = new int[(s - 1) * (s) / 2];
  for (int i = 0; i < s; i++)
  {

    for (int j = 0; j < i + 1; j++)
    {
      new_front[index] = front[i];
      index++;
    }
  }

  back = new_front + s * (s + 1) / 2; // The parenthesis are important!
  delete[] front;
  front = new_front;
}
void even_stepwise_increase(int *&front, int *&back)
{
  // remove all odds.
  int indx = back - front - 1;
  ;
  while (indx >= 0)
  {
    if (front[indx] % 2 != 0)
    {
      erase(front, back, front + indx);
    }
    indx = back - front - 1;
  }
  if (back - front != 1)
  {
    stepwise_increase(front, back);
  }
  else
  {
    front = nullptr;
    back = nullptr;
    cout << "All elements were odd and the array is now empty!" << endl;
  }
}

void random_shuffle(int *front, int size)
{
  int *parry = new int[size]{0};
  for (int *ptr = parry; ptr != parry + size; ptr++)
  {

    *ptr = rand() % 1000 + 1;
  }

  // an array to contain every movement made to the sorting algorithm
  // order random array
  for (size_t i = 0; i < size; i++)
  {
    for (int j = i + 1; j < size; j++)
    {
      if (parry[i] > parry[j])
      {
        int temp = parry[i];
        parry[i] = parry[j];
        parry[j] = temp;
        int frnt_tmp = front[i];
        front[i] = front[j - i];
        front[j - i] = frnt_tmp;
      }
    }
  }

  delete[] parry;
  parry = nullptr;
}
int main()
{

  // Here is the "overhead" for our array,
  // that is, what we need to access and manipulte it.
  int *front, *back; // Pointer to first element of array
  int size;          // Number of elements in the array

  /*IMPORTANT
Work exclusively with one of the two array implementations.
Functions that change the size don't update the back pointer,
and functions that change the back pointer don't update the size.*/

  // I'll work with the double-pointer version

  // Allocate and initialize the array with random numbers from 1-100
  size = 10;
  front = new int[size];
  back = front + size;
  for (int *ptr = front; ptr != back; ptr++)
    *ptr = 6 + 1;

  srand(time(NULL));

  /*  print(front, back);
  cout << "The sum = " << sum(front, back) << endl;

  //Output whether the array contains a set value
  int value = 7;
  if (contains(front, back, value))
          cout << "Array contains " << value << endl;
  else
          cout << "Array does not contain " << value << endl;

  append(front, back, 7);
  //print(front, back); */
  cout << "Print the old, before shuffle" << endl;
  print(front, back);
  cout << "We now print after shuffle\n";
  even_stepwise_increase(front, back);
  print(front, back);

  /*   erase(front, back, find(front, back, 6));
  print(front, back); */
}