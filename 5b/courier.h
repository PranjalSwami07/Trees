/* A courier centre stores parcel codes in a threaded binary search tree, so
that traversal needs no recursion or stack. The codes are taken as input in
order of arrival. Your job is to:
1. 2. 3. Take the user input and insert the parcel codes one by one into a
threaded binary search tree, setting the threads correctly. Count the total
number of threads in the tree. Print the parcel codes in preorder using the
threaded tree, with no recursion and no stack.*/

#include <iostream>

using namespace std;

struct node {
  int parcelCode;
  node *left;
  node *right;
  bool lbit;
  bool rbit;
};

class CourierTBST {
  node *head;

public:
  CourierTBST();
  void insert(int parcelCode);
  void countThreads();
  void preorder();
  void menu();
};