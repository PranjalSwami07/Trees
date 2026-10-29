/* An exam cell stores the roll numbers of arriving students in a binary search
tree, in order of arrival. Your job is to:
1. 2. 3. Take the user input and insert the roll numbers one by one into a
binary search tree. Print the smallest and the largest roll number without using
recursion. Print all roll numbers in ascending order using a non-recursive
inorder traversal with a stack.*/

#include <iostream>
#include <stack>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;

  Node(int val) {
    data = val;
    left = nullptr;
    right = nullptr;
  }
};

class ExamBST {
  Node *root;

public:
  ExamBST();
  void insert(int val);
  void printMinMax();
  void inorderAscending();
  void menu();
};