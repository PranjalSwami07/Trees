/* A railway counter stores ticket numbers in a threaded binary search tree,
where an empty left link points to the inorder predecessor and an empty right
link points to the inorder successor. The ticket numbers are taken as input in
the order they are booked. Your job is to:
1. Take the user input and insert the ticket numbers one by one into a threaded
binary search tree, setting the threads correctly.
2. 3. 4. For every node, print its left and right links, marking each as a real
child or a thread. Print the ticket numbers in ascending order using inorder
traversal on the threaded tree, with no recursion and no stack. For a given
ticket number, find its inorder successor using the threads. */

#include <iostream>

using namespace std;

struct node {
  int ticketNo;
  node *left;
  node *right;
  bool lbit;
  bool rbit;
};

class RailwayTBST {
  node *head;

public:
  RailwayTBST();
  void insert(int ticketNo);
  void displayLinks();
  void inorderAscending();
  void findSuccessor(int ticketNo);
  void menu();
};