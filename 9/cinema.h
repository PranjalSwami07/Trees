/* A cinema stores booked seat numbers in a binary search tree. The seat numbers
are taken as input in the order they are booked. Your job is to:
1. 2. 3. 4. Take the user input and insert the seat numbers one by one into a
binary search tree. Check whether a given seat number is already booked, and
print the number of comparisons made. A booking is cancelled. Remove a given
seat number and print the remaining seat numbers in ascending order. For a given
seat number, print its parent and its sibling, or “none” where they do not
exist.*/

#include <iostream>

using namespace std;

struct Node {
  int seatNo;
  Node *left;
  Node *right;

  Node(int s) {
    seatNo = s;
    left = nullptr;
    right = nullptr;
  }
};

class CinemaBST {
  Node *root;

  Node *insertRec(Node *node, int seatNo);
  Node *findMin(Node *node);
  Node *deleteRec(Node *root, int seatNo, bool &found);
  void inorderRec(Node *node);

public:
  CinemaBST();
  void insert(int seatNo);
  void checkBooking(int seatNo);
  void removeSeat(int seatNo);
  void printParentAndSibling(int seatNo);
  void menu();
};