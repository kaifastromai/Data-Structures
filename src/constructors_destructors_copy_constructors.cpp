#include <iostream>

using namespace std;
class Array
{
private:
    int size;
    int *front;

public:
    Array()
    {
        size = 0;
        front = nullptr;
    }

    Array(int s)
    {
        this->size = s;
        cout << "Alternate constructor called\n";
        if (s <= 0)
        {
            size = 0;
            front = nullptr;
        }
        else
        {
            size = s;
            front = new int[s]{0};
        }
    }
    Array(const Array &org)
    {
        if (org.size <= 0)
        {
            size = 0;
            front = nullptr;
        }
        else{
            
        }
    }
};