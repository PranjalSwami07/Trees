/* A library arranges its books in a binary search tree using each book’s unique
ID. The IDs are taken as input in the order the books arrive. Your job is to:
1. 2. 3. 4. Take the user input and insert the book IDs one by one into a binary
search tree. Print the book IDs in ascending order to confirm the tree is
correct. Remove a given book that has no child or only one child. Print the IDs
in ascending order after removal. Remove a given book that has two children,
using the inorder successor. Print the tree level by level before and after.*/

#include <iostream>
#include <string>

using namespace std;

struct node {
  int id;
  string title;
  node *left;
  node *right;
  bool lbit;
  bool rbit;
};

class tbst {
  node *head;

public:
  tbst();
  void insert(int id, string title);
  void inorder();
  void search(int id);
  void removeBook(int id);
  void levelOrder();
  void menu(); // Encapsulates the entire control flow
};