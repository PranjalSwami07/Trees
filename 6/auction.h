/* An auction site stores bid amounts in a binary search tree. The bids are
taken as input in the order they are placed. Your job is to:
1. 2. 3. Take the user input and insert the bids one by one into a binary search
tree. Print the bids in inorder, preorder and postorder. A bidder withdraws.
Remove a given bid from the tree.4. Print all three traversals again after the
removal.*/

#include <iostream>

using namespace std;

struct Node {
  int bidAmount;
  Node *left;
  Node *right;

  Node(int amount) {
    bidAmount = amount;
    left = nullptr;
    right = nullptr;
  }
};

class AuctionBST {
  Node *root;

  Node *insertRec(Node *node, int amount);
  void inorderRec(Node *node);
  void preorderRec(Node *node);
  void postorderRec(Node *node);
  Node *findMin(Node *node);
  Node *deleteRec(Node *root, int amount, bool &found);

public:
  AuctionBST();
  void insert(int amount);
  void printAllTraversals();
  void removeBid(int amount);
  void menu();
};