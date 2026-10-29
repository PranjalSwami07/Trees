/* A parking lot stores permit numbers in a binary search tree. The permit
numbers are taken as input in the order they are issued. Your job is to:
1. 2. 3. Take the user input and insert the permit numbers one by one into a
binary search tree. Print the permit numbers level by level, from the root
downwards. A permit expires. Remove a given permit and print the permit numbers
level by level after the removal.*/

#include <iostream>

using namespace std;

struct Node {
  int permitNo;
  Node *left;
  Node *right;

  Node(int p) {
    permitNo = p;
    left = nullptr;
    right = nullptr;
  }
};

class ParkingBST {
  Node *root;

  Node *insertRec(Node *node, int permitNo);
  Node *findMin(Node *node);
  Node *deleteRec(Node *root, int permitNo, bool &found);

public:
  ParkingBST();
  void insert(int permitNo);
  void levelOrder();
  void removePermit(int permitNo);
  void menu();
};