 // Binary Search Tree
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
// Globally counts total un-deleted Nodes
int GlobalNodeCounter = 0;

struct BST
{
public:
  struct Node
  {
    int info;
    Node *left;
    Node *right;
    Node(int _info, Node *_left, Node *_right)
    {
      info = _info;
      left = _left;
      right = _right;
      // GlobalNodeCounter incremented
      GlobalNodeCounter++;
    }
    ~Node()
    {
      // GlobalNodeCounter decremented
      GlobalNodeCounter--;
    }
  };

private:
  Node *root;

public:
  // Default constructor
  BST() { root = nullptr; }
  // Copy Constructor Wrapper
  BST(const BST &orig) { root = get_copy(orig.root); }
  // Recursive deep copy of subtree rooted at ptr
  Node *get_copy(Node *ptr)
  {
    if (ptr == nullptr)
      return nullptr;
    return new Node{ptr->info, get_copy(ptr->left), get_copy(ptr->right)};
  }
  // Destructor Wrapper
  ~BST() { clear(root); }

private:
  // Recursive deletion of subtree rooted at ptr. See warning
  // Warning! Calling clear on ptr != root invalidates child link to ptr
  void clear(Node *ptr)
  {
    if (ptr != nullptr)
    {
      clear(ptr->left);
      clear(ptr->right);
    }
    delete ptr;
  }

public:
  // Assignment operator via copy-swap idiom
  BST &operator=(const BST &rhs)
  {
    BST copy(rhs);
    std::swap(root, copy.root);
    return *this;
  }
  // Non-recursive wrapper for recursive print function
  void print()
  {
    print(root);
    cout << endl;
  }
  // Recursive print function prints subtree rooted at ptr
  void print(Node *ptr)
  {
    if (ptr == nullptr)
      cout << '.';
    else
    {
      cout << '(';
      print(ptr->left);
      cout << ' ' << ptr->info << ' ';
      print(ptr->right);
      cout << ')';
    }
  }
  // Non-recursive wrapper for recursive sum function
  int sum() { return sum(root); }
  // Recursive sum function sums subtree rooted at ptr
  int sum(Node *ptr)
  {
    int total = 0;
    if (ptr != nullptr)
    {
      total += ptr->info + sum(ptr->right) + sum(ptr->left);
    }
    return total;
  }
  // Non-recursive wrapper for maximum sum along paths from root to a leaf
  int max_branch_sum()
  {
    return max_branch_sum(root);
  }
  // Recursively finds sum of the path, from ptr to leaf, with max sum
  int max_branch_sum(Node *ptr)
  {

    //we've reached a leaf node
    if (ptr == nullptr)
    {
      return 0;
    }
    int right = max_branch_sum(ptr->right);
    int left = max_branch_sum(ptr->left);

    return ptr->info + (right > left) ? right : left;
  }
  // Non-recursive wrapper for recursive height function
  int height()
  {
    // Empty trees have a height of -1. A root-only tree has height of 0.
    return height(root);
  }
  // Recursive height function gives height of subtree rooted at ptr
  int height(Node *ptr)
  {
    // Empty trees have a height of -1. A root-only tree has height of 0.
    if (ptr == nullptr)
      return -1;
    else
      return 1 + max(height(ptr->left), height(ptr->right));
  }
  // Non-recursive wrapper for recursive size function - counts Nodes
  int size()
  {
    return size(root); // TODO
  }
  // Recursive size function counts Nodes of subtree rooted at ptr
  int size(Node *ptr)
  {
    int count = 0;
    if (ptr != nullptr)
    {
      count++;
      count += size(ptr->right) + size(ptr->left);
    }
    return count;
  }
  ///////////////////////////////////////////////
  Node *find(int val)
  {
    Node *ptr = root;
    while (ptr != nullptr && ptr->info != val)
    {
      if (val < ptr->info)
        ptr = ptr->left;
      else if (val > ptr->info)
        ptr = ptr->right;
    }
    // Returns pointer to Node containing val, else nullptr
    return ptr;
  }
  // Returns level of val (0 if root, -1 if not found)
  int level_of(int val)
  {
    int level = -1;
    Node *ptr = root;
    while (ptr != nullptr)
    {
      if (val < ptr->info)
        ptr = ptr->left;
      else if (val > ptr->info)
        ptr = ptr->right;
      else
      {
        level++;
        break;
      }
      level++;
    }

    // Returns pointer to Node containing val, else nullptr
    if (ptr != nullptr)
      return level;
    else
    {
      return -1;
    }
  }
  // Inserts val in tree, maintaining BST ordering property
  bool insert(int val)
  {
    if (root == nullptr)
    {
      root = new Node{val, nullptr, nullptr};
      return true;
    }
    Node *ptr = root;
    while (ptr != nullptr)
    {
      if (val < ptr->info)
      {
        if (ptr->left == nullptr)
          ptr = ptr->left = new Node{val, nullptr, nullptr};
        ptr = ptr->left;
      }
      else if (val > ptr->info)
      {
        if (ptr->right == nullptr)
          ptr = ptr->right = new Node{val, nullptr, nullptr};
        ptr = ptr->right;
      }
      else // We don't allow duplicates
        return false;
    }
    return true;
  }
  void polyinsert(int val)
  {
    if (root == nullptr)
    {
      root = new Node{val, nullptr, nullptr};
      return;
    }
    Node *ptr = root;
    while (ptr != nullptr)
    {
      if (val < ptr->info)
      {
        if (ptr->left == nullptr)
          ptr = ptr->left = new Node{val, nullptr, nullptr};
        ptr = ptr->left;
      }
      else if (val > ptr->info)
      {
        if (ptr->right == nullptr)
          ptr = ptr->right = new Node{val, nullptr, nullptr};
        ptr = ptr->right;
      }
      else
      {
        Node *old_subroot = ptr;
        if (rand() % 2 == 0)
          ptr = new Node{val, old_subroot, nullptr};
        else
          ptr = new Node{val, nullptr, old_subroot};
      }
    }
  }
  // Erases val from tree, maintaining BST ordering property
  // The erase function returns false if val is not in tree
  bool erase(int val)
  {

    // Step 1: Find the Node to be erased and its parent.
    //Assume every element is unique, we find the node who has a child of val;
    Node *ptr = root; // Node to be erased

    Node *parent; // Parent of Node to be erased
    while (ptr != nullptr && ptr->right->info != val && ptr->left->info != val)
    {
      if (val < ptr->left->info || val < ptr->left->info)
        ptr = ptr->left;
      else if (val > ptr->right->info || val > ptr->right->info)
        ptr = ptr->right;
    }
    if (ptr != nullptr)
    {
      parent = ptr;
      if (parent->left->info == val)
        ptr = parent->left;
      if (parent->right->info == val)
        ptr = parent->right;
      //***Your Code Here

      // At this point,
      // ptr points to Node to be erased
      // parent points to the parent of Node to be erased

      // Step 2: Consider the case where ptr has two children.
      if (ptr->left != nullptr && ptr->right != nullptr)
      {
        // Replace ptr's info with the info of ptr's successor.
        Node *suc_parent = ptr->right;
        Node *suc;
        if (suc_parent->left != nullptr)
        {
          suc = ptr->right;
        }

        while (suc_parent->left != nullptr)
        {
          suc_parent = suc_parent->left;
        }
        ptr->info = suc_parent->left->info;

        delete suc_parent->left;
        suc->left = nullptr;

        //***Your Code Here
        // Then reset the original ptr and parent to be the successor and its
        // parent.

        //***Your Code Here
      }

      // ptr may or may not have been modified above, but at this point,
      // ptr points to a Node to be erased, which doesn't have 2 children, and
      // parent points to the parent of the Node to be erased

      // Step 3: The link from *parent to *ptr needs to bypass *ptr and point to a
      // child of *ptr, possibly nullptr if ptr has no children.

      //***Your Code Here

      if (ptr->right != nullptr)
      {
        Node *suc_parent = ptr->right;
        Node *suc;
        if (suc_parent->left != nullptr)
        {
          suc = ptr->right;
        }

        while (suc_parent->left != nullptr)
        {
          suc_parent = suc_parent->left;
        }
        ptr->info = suc_parent->left->info;

        delete suc_parent->left;
        suc->left = nullptr;
      }
      else
      {
        return false;
      }

      // Better Check:
      // Did you actually delete a Node to free memory?
      // What happens if the tree is empty?
      // What happens if the tree is root-only with the value in the root?
      // What happens if the tree is root-only with the value not in the root?

      // Run the tests in main and make sure that they give the correct output.

      return true;
    }
  }
};

int main()
{
  cout << "Testing BST with insertion order {4, 2, 6, 1, 3, 5, 7, 8}\n";
  BST tree; // Default constructor for empty tree
  {
    BST t1;
    for (int i : {4, 2, 6, 1, 3, 5, 7, 8})
    {
      t1.insert(i);
      t1.print();
    }
    cout << "NodeCounter after t1   = " << GlobalNodeCounter << endl
         << endl;

    cout << "Testing Copy Constructor, Assignment, and Destructor\n";
    BST t2 = t1; // Copy Constructor
    cout << "NodeCounter after t2   = " << GlobalNodeCounter << endl;
    tree = t2; // Assignment Operator
    cout << "NodeCounter after tree = " << GlobalNodeCounter << endl;
  } // Calls destructor on t1 and t2
  cout << "NodeCounter with only tree = " << GlobalNodeCounter << endl;
  cout << "Levels should output 3 0 -1. Actual output is: " << tree.level_of(8)
       << ' ' << tree.level_of(4) << ' ' << tree.level_of(9) << endl
       << endl;

  cout << "Stats on tree:  " << endl;
  // tree.print();
  cout << "Sum = " << tree.sum() << " Height = " << tree.height()
       << " Size = " << tree.size() << " NodeCounter = " << GlobalNodeCounter
       << " Max branch sum = " << tree.max_branch_sum() << endl;
  cout << "Run a test of level_of here: " << endl
       << endl;

  BST temp_tree = tree;
  for (int i = 1; i <= 8; i++)
  {
    cout << "Erasing " << i << " from temporary copy of tree:  ";
    temp_tree.erase(i);
    temp_tree.print();
    cout << "Sum = " << temp_tree.sum() << " Height = " << temp_tree.height()
         << " Size = " << temp_tree.size()
         << " NodeCounter = " << GlobalNodeCounter
         << " Max branch sum = " << temp_tree.max_branch_sum() << endl
         << endl;
  }
  return 0;
}
