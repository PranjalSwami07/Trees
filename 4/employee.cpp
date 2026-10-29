#include "employee.h"

EmployeeBST::EmployeeBST()
{
    root = nullptr;
}

Node* EmployeeBST::insertRec(Node* node, int id)
{
    if (node == nullptr)
    {
        return new Node(id);
    }
    if (id < node->id)
    {
        node->left = insertRec(node->left, id);
    }
    else if (id > node->id)
    {
        node->right = insertRec(node->right, id);
    }
    else
    {
        cout << "Employee ID " << id << " already exists." << endl;
    }
    return node;
}

void EmployeeBST::insert(int id)
{
    root = insertRec(root, id);
    cout << "Employee ID " << id << " inserted successfully." << endl;
}

int EmployeeBST::heightRec(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int leftHeight = heightRec(node->left);
    int rightHeight = heightRec(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void EmployeeBST::printHeight()
{
    int h = heightRec(root);
    cout << "Height of the tree: " << h << endl;
}

void EmployeeBST::preorderNonRecursive()
{
    if (root == nullptr)
    {
        cout << "The tree is empty." << endl;
        return;
    }

    stack<Node*> s;
    s.push(root);

    cout << "Preorder Traversal (Non-Recursive): ";
    while (!s.empty())
    {
        Node* curr = s.top();
        s.pop();

        cout << curr->id << " ";

        if (curr->right != nullptr)
        {
            s.push(curr->right);
        }
        if (curr->left != nullptr)
        {
            s.push(curr->left);
        }
    }
    cout << endl;
}

void EmployeeBST::menu()
{
    int choice, id;
    do
    {
        cout << "\n--- Company Employee BST Management ---\n"
             << "1. Insert Employee ID\n"
             << "2. Print Height of Tree\n"
             << "3. Print Preorder Traversal (Non-Recursive)\n"
             << "4. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Employee ID: ";
            cin >> id;
            insert(id);
            break;

        case 2:
            printHeight();
            break;

        case 3:
            preorderNonRecursive();
            break;

        case 4:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}