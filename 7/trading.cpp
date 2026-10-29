#include "trading.h"

TradingBST::TradingBST()
{
    root = nullptr;
}

Node* TradingBST::insertRec(Node* node, int price)
{
    if (node == nullptr)
    {
        return new Node(price);
    }
    if (price < node->price)
    {
        node->left = insertRec(node->left, price);
    }
    else if (price > node->price)
    {
        node->right = insertRec(node->right, price);
    }
    else
    {
        cout << "Stock price " << price << " already exists." << endl;
    }
    return node;
}

void TradingBST::insert(int price)
{
    root = insertRec(root, price);
    cout << "Stock price " << price << " inserted successfully." << endl;
}

void TradingBST::findFloorRec(Node* node, int val, int &floorVal, bool &found)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->price == val)
    {
        floorVal = node->price;
        found = true;
        return;
    }

    if (node->price > val)
    {
        // Floor must be in the left subtree
        findFloorRec(node->left, val, floorVal, found);
    }
    else
    {
        // Current node could be a floor candidate, look right for a closer (larger) one
        floorVal = node->price;
        found = true;
        findFloorRec(node->right, val, floorVal, found);
    }
}

void TradingBST::printFloor(int val)
{
    if (root == nullptr)
    {
        cout << "none" << endl;
        return;
    }

    int floorVal = -1;
    bool found = false;
    findFloorRec(root, val, floorVal, found);

    if (found)
    {
        cout << "Floor of " << val << " is: " << floorVal << endl;
    }
    else
    {
        cout << "none" << endl;
    }
}

Node* TradingBST::findMin(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node* TradingBST::deleteRec(Node* root, int price, bool &found)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (price < root->price)
    {
        root->left = deleteRec(root->left, price, found);
    }
    else if (price > root->price)
    {
        root->right = deleteRec(root->right, price, found);
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
        root->price = temp->price;
        root->right = deleteRec(root->right, temp->price, found);
    }
    return root;
}

void TradingBST::inorderRec(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    inorderRec(node->left);
    cout << node->price << " ";
    inorderRec(node->right);
}

void TradingBST::removePrice(int price)
{
    if (root == nullptr)
    {
        cout << "Stock price tree is empty." << endl;
        return;
    }

    bool found = false;
    root = deleteRec(root, price, found);

    if (found)
    {
        cout << "Stock price " << price << " successfully removed." << endl;
        cout << "Remaining Prices in Ascending Order: ";
        inorderRec(root);
        cout << endl;
    }
    else
    {
        cout << "Stock price " << price << " not found in the tree." << endl;
    }
}

void TradingBST::menu()
{
    int choice, price;
    do
    {
        cout << "\n--- Trading App Stock Price BST --- \n"
             << "1. Insert Stock Price\n"
             << "2. Find Floor of a Given Price\n"
             << "3. Remove a Mistaken Price (Print Ascending Order)\n"
             << "4. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Closing Price: ";
            cin >> price;
            insert(price);
            break;

        case 2:
            cout << "Enter value to find floor for: ";
            cin >> price;
            printFloor(price);
            break;

        case 3:
            cout << "Enter Closing Price to remove: ";
            cin >> price;
            removePrice(price);
            break;

        case 4:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}