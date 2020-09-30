#include <iostream>
using namespace std;
struct RGB
{
    int r, g, b;
    //Do not give RGB a constructor. Its three integer members are uninitialized.
};
struct Pict
{
    Pict(int num_rows, int num_cols)
    {
        rows = num_rows;
        cols = num_cols;
        ptr = new RGB[num_rows * num_cols]{0};
    }
    //Data members of Pict
    int rows; //Number of rows in the Pict
    int cols; //Number of columns in the Pict
    RGB *ptr; //Pointer to an array of RGB pixels
    ~Pict()
    {
        delete[] ptr;
    }
};

int main()
{
    Pict p(32, 24); //Declares a Pict struct p having 32 rows and 24 columns
   
}
//I'm a might bemused at this project. Is this it? It seems really, really easy...