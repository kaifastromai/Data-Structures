#include <iostream>

class bin_tree {
  struct Node {
    int val;
    Node *left;
    Node *right;
  };

  Node *root;

  bin_tree(int a[]) {
    if (sizeof(a) > 0) {
      root->val = a[0];
      root->left = nullptr;
      root->right = nullptr;
      rec_construct(root,a);
    }
  }
  void rec_construct(Node *ptr, int a[]) {
    int it_loc = 1;
    if (it_loc != sizeof(a)) {
      ptr->left = new Node;
      ptr->left->val = a[it_loc];
      ptr->left->left = nullptr;
      ptr->left->right = nullptr;
      it_loc++;
      rec_construct(ptr->left, a);

      ptr->right = new Node;
      ptr->right->val = a[it_loc];
      ptr->right->left = nullptr;
      ptr->right->right = nullptr;
      it_loc++;
      rec_construct(ptr->right,a);
    }
  }
};

