#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <list>
using namespace std;
struct kvPair
{
    string key;
    int value;
    kvPair(string key = "", int value = 0)
    {
        this->key = key;
        this->value = value;
    }
    bool is_empty() { return key == ""; }
};
class AssocArray
{
protected:
    vector<kvPair> buckets;
    size_t num_buckets{32};
    int hash_function(string key);

public:
    AssocArray();
    void insert(string key, int val);
    int size();
    void print();
    bool erase(string key);
    int count(string key);
    int get_val(string key);
    void resize(int new_size);
};
void AssocArray::resize(int new_size)
{
    if (new_size > buckets.size())
    {
        auto old_bucket = buckets;
        buckets.clear();
        buckets.resize(new_size);

        for (auto kvp : old_bucket)
        {
            insert(kvp.key, kvp.value);
        }
    }
}
int AssocArray::get_val(string key)
{
    if (count(key) == 1)
        return buckets.at(hash_function(key)).value;
    else
        return 0;
}
int AssocArray::count(string key)
{
    if (buckets.at(hash_function(key)).key == key)
        return 1;
    else
        return 0;
}
bool AssocArray::erase(string key)
{
    try
    {
        buckets.erase(buckets.begin() + hash_function(key));
        return true;
    }
    //catch all exceptions with erasure
    catch (...)
    {
        return false;
    }
}
AssocArray::AssocArray()
{
    buckets = vector<kvPair>{num_buckets};
};
int AssocArray::hash_function(string key)
{
    hash<string> stl_hash_function;
    return stl_hash_function(key) % buckets.size();
}
void AssocArray::insert(string key, int val)
{
    kvPair kvp{key, val};
    buckets.at(hash_function(key)) = kvp;
}
int AssocArray::size()
{
    int sz = 0;
    for (auto item : buckets)
    {
        if (!item.is_empty())
            sz++;
    }
    return sz;
}
void AssocArray::print()
{
    for (auto kvp : buckets)
    {
        if (!kvp.is_empty())
        {
            cout << "(" << kvp.key << ", " << kvp.value << ")" << endl;
        }
    }
}

class AssocArrayOA : public AssocArray
{
public:
    void insert(string key, int val);
};

void AssocArrayOA::insert(string key, int val)
{
    int indx = hash_function(key);
    if (!buckets.at(indx).is_empty())
    {
        while (!buckets.at(indx).is_empty())
        {
            if (indx == buckets.size())
                indx = 0;

            if (buckets.at(indx++).is_empty())
            {
                buckets.at(indx) = kvPair{key, val};
                break;
            }
        }
    }
    else
        buckets.at(indx) = kvPair{key, val};
}
int main()
{
    AssocArrayOA umap;
    for (char ch = 'a'; ch <= 'z'; ch++)
        umap.insert(string("key_") + ch, rand());
    umap.print();
    cout << "size = " << umap.size() << endl;
    umap.resize(64);
    cout << "\nAfter resizing, same items but different order:\n\n";
    umap.print();
    cout << "size = " << umap.size() << endl;
}

class AssocArraySC
{
public:
    AssocArraySC() { buckets.resize(num_buckets); }
    void insert(string key, int value);
    int size();
    void print();
    bool erase(string key);
    int count(string key);
    int get_value(string key);

protected:
    vector<list<kvPair>> buckets;
    int num_buckets = 32; //initial size
    int hash_function(string key)
    {
        //must #include <functional>
        hash<string> stl_hash_function;
        return stl_hash_function(key) % buckets.size();
    }
};
void AssocArraySC::insert(string key, int value)
{

    kvPair kvp{key, value};
    buckets.at(hash_function(key)).push_back(kvp);
}
int AssocArraySC::size()
{
    int sz = 0;
    for (auto list : buckets)
    {
        for (auto kvp : list)
        {
            if (!kvp.is_empty())
            {
                sz++;
            }
        }
    }
    return sz;
}
bool AssocArraySC::erase(string key)
{
    auto &list = buckets.at(hash_function(key));
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (it->key == key)
        {
            list.erase(it);
            return true;
        }
    }
    return false;
} //Returns true when successful
int AssocArraySC::count(string key)
{
    auto &list = buckets.at(hash_function(key));
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (it->key == key)
        {
            return 1;
        }
    }
    return 0;
}
int AssocArraySC::get_value(string key)
{
    auto &list = buckets.at(hash_function(key));
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (it->key == key)
        {
            return it->value;
        }
    }
    return 0;
}