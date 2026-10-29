#include "hospital.h"

HospitalBST::HospitalBST()
{
    root = nullptr;
}

Node* HospitalBST::insertRec(Node* node, int token)
{
    if (node == nullptr)
    {
        return new Node(token);
    }
    if (token < node->token)
    {
        node->left = insertRec(node->left, token);
    }
    else if (token > node->token)
    {
        node->right = insertRec(node->right, token);
    }
    else
    {
        cout << "Token " << token << " already exists." << endl;
    }
    return node;
}

void HospitalBST::insert(int token)
{
    root = insertRec(root, token);
    cout << "Token " << token << " inserted successfully." << endl;
}

int HospitalBST::countLeavesRec(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    if (node->left == nullptr && node->right == nullptr)
    {
        return 1;
    }
    return countLeavesRec(node->left) + countLeavesRec(node->right);
}

void HospitalBST::printLeafCount()
{
    int count = countLeavesRec(root);
    cout << "Number of leaf nodes in the tree: " << count << endl;
}

Node* HospitalBST::findMin(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node* HospitalBST::deleteRec(Node* root, int token, bool &found)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (token < root->token)
    {
        root->left = deleteRec(root->left, token, found);
    }
    else if (token > root->token)
    {
        root->right = deleteRec(root->right, token, found);
    }
    else
    {
        found = true;
        // Node with 0 or 1 child
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

        // Node with 2 children
        Node* temp = findMin(root->right);
        root->token = temp->token;
        root->right = deleteRec(root->right, temp->token, found);
    }
    return root;
}

void HospitalBST::removeSingleToken(int token)
{
    if (root == nullptr)
    {
        cout << "Waiting queue is empty." << endl;
        return;
    }

    cout << "\n--- Tree BEFORE Removal ---" << endl;
    levelOrder();

    bool found = false;
    root = deleteRec(root, token, found);

    if (found)
    {
        cout << "Token " << token << " removed successfully." << endl;
    }
    else
    {
        cout << "Token " << token << " not found in the queue." << endl;
    }

    cout << "\n--- Tree AFTER Removal ---" << endl;
    levelOrder();
}

void HospitalBST::removeMultipleTokens()
{
    if (root == nullptr)
    {
        cout << "Waiting queue is empty." << endl;
        return;
    }

    int n;
    cout << "Enter how many tokens you want to remove: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int token;
        cout << "Enter token " << (i + 1) << " to remove: ";
        cin >> token;
        bool found = false;
        root = deleteRec(root, token, found);
        if (found)
        {
            cout << "Token " << token << " removed." << endl;
        }
        else
        {
            cout << "Token " << token << " not found." << endl;
        }
    }

    cout << "\nRemaining Tokens in Ascending Order: ";
    inorderRec(root);
    cout << endl;
}

void HospitalBST::inorderRec(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    inorderRec(node->left);
    cout << node->token << " ";
    inorderRec(node->right);
}

void HospitalBST::levelOrder()
{
    if (root == nullptr)
    {
        cout << "Queue is empty." << endl;
        return;
    }

    Node* q[100];
    int front = 0, rear = 0;
    q[rear++] = root;

    cout << "-----------------------------" << endl;
    while (front < rear)
    {
        Node* curr = q[front++];
        cout << "Token: " << curr->token << endl;

        if (curr->left)
        {
            q[rear++] = curr->left;
        }
        if (curr->right)
        {
            q[rear++] = curr->right;
        }
    }
    cout << "-----------------------------" << endl;
}

void HospitalBST::menu()
{
    int choice, token;
    do
    {
        cout << "\n--- Hospital Waiting Queue (BST) ---\n"
             << "1. Insert Token\n"
             << "2. Print Number of Leaf Nodes\n"
             << "3. Remove a Patient Token (Print Level Order Before & After)\n"
             << "4. Remove Multiple Tokens (Print Remaining in Ascending Order)\n"
             << "5. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Token Number: ";
            cin >> token;
            insert(token);
            break;

        case 2:
            printLeafCount();
            break;

        case 3:
            cout << "Enter Token Number to remove: ";
            cin >> token;
            removeSingleToken(token);
            break;

        case 4:
            removeMultipleTokens();
            break;

        case 5:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}