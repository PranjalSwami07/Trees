/*A hospital keeps its waiting patients in a binary search tree by token number.
The tokens are taken as input in the order they are issued. Your job is to:
1. 2. 3. 4. Take the user input and insert the tokens one by one into a binary
search tree. Print the number of leaf nodes in the tree. A patient leaves.
Remove a given token and print the tree level by level before and after. Remove
several given tokens one after another and print the remaining tokens in
ascending order.*/

#include <iostream>

using namespace std;

struct Node {
  int token;
  Node *left;
  Node *right;

  Node(int t) {
    token = t;
    left = nullptr;
    right = nullptr;
  }
};

class HospitalBST {
  Node *root;

  Node *insertRec(Node *node, int token);
  int countLeavesRec(Node *node);
  Node *findMin(Node *node);
  Node *deleteRec(Node *root, int token, bool &found);
  void inorderRec(Node *node);

public:
  HospitalBST();
  void insert(int token);
  void printLeafCount();
  void removeSingleToken(int token);
  void removeMultipleTokens();
  void levelOrder();
  void menu();
};