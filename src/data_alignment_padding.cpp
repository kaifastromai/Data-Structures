#include <string>
#include <iostream>
using namespace std;

struct Foo
{
    string first_name;
    char middle_initial;
    string last_name;
};

int main()
{
    Foo f;
    f.first_name = "Frank";
    f.middle_initial = 'C';
    f.last_name = "Clerkson";
    cout << "Foo size: " << sizeof(f) << " Size of first_name: "
         << sizeof(f.first_name) << " Size of middle_initial: "
         << sizeof(f.middle_initial)
         << " Size of last_name: "
         << sizeof(f.last_name) << endl;
    cout << "Address f: " << (int)&f << "\n"
         << "Address first_name: " << (int)&f.first_name << "\n"
         << "middle_initial: " << (int)&f.middle_initial << "\n"
         << "Address last_name: " << (int)&f.last_name << endl;
    *(&f.middle_initial + 1) = 'A';
    *(&f.middle_initial + 2) = 'B';
    *(&f.middle_initial + 3) = 'C';
    char *ptr = &f.middle_initial + 1;
    cout << "Char at +1: " << *ptr;
}