#include <iostream>
#include <vector>
#include <fstream>
const int NUM_ROLLS = 100;
const int MAX_VALUE = 100;
const int NUM_TRIALS = 10000;
using namespace std;
int main()
{
    vector<int> dist(MAX_VALUE + 1);
    for (int trials = 1; trials <= NUM_TRIALS; trials++)
    {
        dist[num_unique1()]++;
    }
    ofstream fout("dist.csv");
    for (int i=0; i <= NUM_ROLLS; i++)
    {
        fout << dist[i] << endl;
    }
}
int num_unique1()
{
    vector<int> outcomes;
    for (int rolls = 1; rolls <= NUM_ROLLS; rolls++)
    {
        int val = rand() % MAX_VALUE + 1;
        if (find(outcomes.begin(), outcomes.end(), val) == outcomes.end())
        {
            outcomes.push_back(val);
        }
    }
    return outcomes.size();
}