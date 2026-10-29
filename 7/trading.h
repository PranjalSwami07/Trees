/* A trading app stores the closing prices of a stock in a binary search tree.
The prices are taken as input in the order they are recorded. Your job is to:
1. 2. 3. Take the user input and insert the prices one by one into a binary
search tree. For a given value, print the largest price in the tree that is not
greater than it (the floor). Print “none” if there is no such price. A price was
entered by mistake. Remove a given price and print the remaining prices in
ascending order.*/

#include <iostream>

using namespace std;

struct Node {
  int price;
  Node *left;
  Node *right;

  Node(int p) {
    price = p;
    left = nullptr;
    right = nullptr;
  }
};

class TradingBST {
  Node *root;

  Node *insertRec(Node *node, int price);
  void findFloorRec(Node *node, int val, int &floorVal, bool &found);
  Node *findMin(Node *node);
  Node *deleteRec(Node *root, int price, bool &found);
  void inorderRec(Node *node);

public:
  TradingBST();
  void insert(int price);
  void printFloor(int val);
  void removePrice(int price);
  void menu();
};