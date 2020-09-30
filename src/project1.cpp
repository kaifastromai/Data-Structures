#include <iostream>
#include <string>
#include <new>
#include <time.h>
using namespace std;
int loop_pointer_array()
{

    srand(time(NULL));
    int a[100];

    for (int *ptr = a; ptr != a + 100; ptr++)
    {
        *ptr = rand() % 31 + 10;
        //cout << "A[]: " << a[ptr - a] << endl;
    }

    int *parr[100];
    for (int **ptr = parr; ptr != parr + 100; ptr++)
    {
        *ptr = new int[a[ptr - parr]];
        //cout << "Ptr-parr: " << ptr - parr << endl;
        for (int *p = *ptr; p != *ptr + a[ptr - parr]; p++)
        {

            *p = rand() % (a[ptr - parr]) + 1;
            // cout << "**ptr: " << **ptr << endl;
        }
    }

    size_t total = 0;
    for (size_t i = 0; i < 100; i++)
    {
        for (size_t j = 0; j < a[i]; j++)
        {

            total += parr[i][j];
            //cout << "Par[i][j]: " << parr[i][j] << endl;
        }
        delete[] parr[i];
    }
    return total;
}
int main()
{
    int iterations = 1000;
    size_t super_sum = 0;
    for (size_t i = 0; i < iterations; i++)
    {
        super_sum += loop_pointer_array();
    }

    cout << "Average: " << super_sum / iterations << endl;
}