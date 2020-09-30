// rememb-o-matic
#include <iostream>
#include <string>
#include <new>
using namespace std;

int main()
{
    int a[7] = {1, 2, 3, 4, 5, 6, 7};
    cout << *(a + 3) << endl; //1
    int *ptr = &a[3];
    cout << *ptr << endl;//2
    cout << *(&a[3]) << endl;//3
    int *ptr1 = &a[7];
    cout << *(ptr1 - 4) << endl;//4
    void *vptr = &a[1];
    cout << *(static_cast<int *>(vptr) + 2) << endl;//5
    ;
    int *ptr2 = ptr1;
    cout << *(ptr2 - 4) << endl;//6
    for (int *p = a; p != a + 7; p++)
    {
        if (p == a + 3)
        {
            cout << *p << endl;//7
        }
    }
    int *p3 = a;
    int *p4 = a + 1;
    int *p5 = p4 + 1;
    int *p6 = p5 + 1;
    cout << *p6 << endl;//8
}