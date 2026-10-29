#include "permit.h"

ParkingBST::ParkingBST()
{
    root = nullptr;
}

Node* ParkingBST::insertRec(Node* node, int permitNo)
{
    if (node == nullptr)
    {
        return new Node(permitNo);
    }
    if (permitNo < node->permitNo)
    {
        node->left = insertRec(node->left, permitNo);
    }
    else if (permitNo > node->permitNo)
    {
        node->right = insertRec(node->right, permitNo);
    }
    else
    {
        cout << "Permit number " << permitNo << " already exists." << endl;
    }
    return node;
}

void ParkingBST::insert(int permitNo)
{
    root = insertRec(root, permitNo);
    cout << "Permit number " << permitNo << " inserted successfully." << endl;
}

void ParkingBST::levelOrder()
{
    if (root == nullptr)
    {
        cout << "Parking lot BST is empty." << endl;
        return;
    }

    Node* q[100];
    int front = 0, rear = 0;
    q[rear++] = root;

    cout << "--- Level-Order Traversal ---" << endl;
    while (front < rear)
    {
        Node* curr = q[front++];
        cout << "Permit: " << curr->permitNo << endl;

        if (curr->left != nullptr)
        {
            q[rear++] = curr->left;
        }
        if (curr->right != nullptr)
        {
            q[rear++] = curr->right;
        }
    }
    cout << "-----------------------------" << endl;
}

Node* ParkingBST::findMin(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node* ParkingBST::deleteRec(Node* root, int permitNo, bool &found)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (permitNo < root->permitNo)
    {
        root->left = deleteRec(root->left, permitNo, found);
    }
    else if (permitNo > root->permitNo)
    {
        root->right = deleteRec(root->right, permitNo, found);
    }
    else
    {
        found = true;
        // Case 1: 0 or 1 child
        if (root->left == nullptr)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 2: 2 children (get inorder successor)
        Node* temp = findMin(root->right);
        root->permitNo = temp->permitNo;
        root->right = deleteRec(root->right, temp->permitNo, found);
    }
    return root;
}

void ParkingBST::removePermit(int permitNo)
{
    if (root == nullptr)
    {
        cout << "Parking lot BST is empty." << endl;
        return;
    }

    bool found = false;
    root = deleteRec(root, permitNo, found);

    if (found)
    {
        cout << "Permit " << permitNo << " expired and was removed successfully." << endl;
        cout << "\nLevel-Order Traversal After Removal:" << endl;
        levelOrder();
    }
    else
    {
        cout << "Permit number " << permitNo << " not found." << endl;
    }
}

void ParkingBST::menu()
{
    int choice, permitNo;
    do
    {
        cout << "\n--- Parking Lot Permit Management --- \n"
             << "1. Insert Permit Number\n"
             << "2. Print Level-Order Traversal\n"
             << "3. Remove Expired Permit (Print Level-Order After Removal)\n"
             << "4. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Permit Number: ";
            cin >> permitNo;
            insert(permitNo);
            break;

        case 2:
            levelOrder();
            break;

        case 3:
            cout << "Enter Permit Number to remove: ";
            cin >> permitNo;
            removePermit(permitNo);
            break;

        case 4:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}