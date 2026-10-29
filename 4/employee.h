/* A company stores employee ID numbers in a binary search tree, in order of
joining. Your job is to:
1. 2. 3. Take the user input and insert the employee IDs one by one into a
binary search tree. Print the height of the tree. Print the IDs in preorder
using a non-recursive method with a stack.*/

#include <iostream>
#include <stack>

using namespace std;

struct Node {
  int id;
  Node *left;
  Node *right;

  Node(int val) {
    id = val;
    left = nullptr;
    right = nullptr;
  }
};

class EmployeeBST {
  Node *root;

  Node *insertRec(Node *node, int id);
  int heightRec(Node *node);

public:
  EmployeeBST();
  void insert(int id);
  void printHeight();
  void preorderNonRecursive();
  void menu();
};