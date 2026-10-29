#include "exambst.h"

ExamBST::ExamBST()
{
    root = nullptr;
}

void ExamBST::insert(int val)
{
    Node* newNode = new Node(val);
    if (root == nullptr)
    {
        root = newNode;
        cout << "Roll number inserted successfully." << endl;
        return;
    }

    Node* curr = root;
    Node* parent = nullptr;

    while (curr != nullptr)
    {
        parent = curr;
        if (val == curr->data)
        {
            cout << "Roll number already exists." << endl;
            delete newNode;
            return;
        }
        else if (val < curr->data)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    if (val < parent->data)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }
    cout << "Roll number inserted successfully." << endl;
}

void ExamBST::printMinMax()
{
    if (root == nullptr)
    {
        cout << "The tree is empty." << endl;
        return;
    }

    // Smallest is the leftmost node (non-recursive)
    Node* currMin = root;
    while (currMin->left != nullptr)
    {
        currMin = currMin->left;
    }

    // Largest is the rightmost node (non-recursive)
    Node* currMax = root;
    while (currMax->right != nullptr)
    {
        currMax = currMax->right;
    }

    cout << "Smallest Roll Number: " << currMin->data << endl;
    cout << "Largest Roll Number: " << currMax->data << endl;
}

void ExamBST::inorderAscending()
{
    if (root == nullptr)
    {
        cout << "The tree is empty." << endl;
        return;
    }

    stack<Node*> s;
    Node* curr = root;

    cout << "Roll Numbers in Ascending Order: ";
    while (curr != nullptr || !s.empty())
    {
        while (curr != nullptr)
        {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        cout << curr->data << " ";

        curr = curr->right;
    }
    cout << endl;
}

void ExamBST::menu()
{
    int choice, val;
    do
    {
        cout << "\n--- Exam Cell BST Management ---\n"
             << "1. Insert Roll Number\n"
             << "2. Print Smallest and Largest Roll Number\n"
             << "3. Print Roll Numbers in Ascending Order (Inorder)\n"
             << "4. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Roll Number: ";
            cin >> val;
            insert(val);
            break;

        case 2:
            printMinMax();
            break;

        case 3:
            inorderAscending();
            break;

        case 4:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}