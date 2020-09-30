#include <iostream>
#include <vector>
using namespace std;

int GLOBAL_NODE_COUNTER = 0;
struct Node
{
  int data;
  std::vector<Node *> children;
  Node(int data = 0)
  {
    this->data = data;
    GLOBAL_NODE_COUNTER++;
  }
  ~Node()
  {
    GLOBAL_NODE_COUNTER--;
    cout << "delete " << data << endl;
  }
  void add_child(int data);
};
void Node::add_child(int data)
{
  Node *n = new Node;
  n->data = data;
  children.push_back(n);
}

void print_preoder(Node *node)
{
  cout << node->data << ", ";
  for (auto child : node->children)
  {
    print_preoder(child);
  }
}
int main()
{
  Node *root = new Node(1);
  root->add_child(2);
  root->add_child(3);
  root->add_child(4);

  Node *n;
  n = root->children[0];
  n->add_child(5);
  n->add_child(6);
  n->add_child(7);

  n = root->children[1];
  n->add_child(8);

  n = root->children[2];
  n->add_child(9);
  n->add_child(10);
  n = n->children[1];
  n->add_child(11);
  n->add_child(12);

  cout << GLOBAL_NODE_COUNTER << endl;
  print_preoder(root);
  cout << endl;

  // delete them the slow way:
  delete n->children[1];
  delete n->children[0];
  delete n;
  n = root->children[2];
  delete n->children[0];
  n = root->children[2];
  delete n;
  delete root->children[1]->children[0];
  delete root->children[1];
  delete root->children[0]->children[2];
  delete root->children[0]->children[1];
  delete root->children[0]->children[0];
  delete root->children[0];
  delete root;
  cout << GLOBAL_NODE_COUNTER << endl;
}
