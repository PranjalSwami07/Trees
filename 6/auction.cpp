#include "auction.h"

AuctionBST::AuctionBST()
{
    root = nullptr;
}

Node* AuctionBST::insertRec(Node* node, int amount)
{
    if (node == nullptr)
    {
        return new Node(amount);
    }
    if (amount < node->bidAmount)
    {
        node->left = insertRec(node->left, amount);
    }
    else if (amount > node->bidAmount)
    {
        node->right = insertRec(node->right, amount);
    }
    else
    {
        cout << "Bid amount " << amount << " already exists." << endl;
    }
    return node;
}

void AuctionBST::insert(int amount)
{
    root = insertRec(root, amount);
    cout << "Bid amount " << amount << " inserted successfully." << endl;
}

void AuctionBST::inorderRec(Node* node)
{
    if (node == nullptr)
        return;
    inorderRec(node->left);
    cout << node->bidAmount << " ";
    inorderRec(node->right);
}

void AuctionBST::preorderRec(Node* node)
{
    if (node == nullptr)
        return;
    cout << node->bidAmount << " ";
    preorderRec(node->left);
    preorderRec(node->right);
}

void AuctionBST::postorderRec(Node* node)
{
    if (node == nullptr)
        return;
    postorderRec(node->left);
    postorderRec(node->right);
    cout << node->bidAmount << " ";
}

void AuctionBST::printAllTraversals()
{
    if (root == nullptr)
    {
        cout << "The auction tree is empty." << endl;
        return;
    }

    cout << "\n--- Tree Traversals ---" << endl;
    cout << "Inorder:   ";
    inorderRec(root);
    cout << endl;

    cout << "Preorder:  ";
    preorderRec(root);
    cout << endl;

    cout << "Postorder: ";
    postorderRec(root);
    cout << endl;
    cout << "-----------------------" << endl;
}

Node* AuctionBST::findMin(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node* AuctionBST::deleteRec(Node* root, int amount, bool &found)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (amount < root->bidAmount)
    {
        root->left = deleteRec(root->left, amount, found);
    }
    else if (amount > root->bidAmount)
    {
        root->right = deleteRec(root->right, amount, found);
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
        root->bidAmount = temp->bidAmount;
        root->right = deleteRec(root->right, temp->bidAmount, found);
    }
    return root;
}

void AuctionBST::removeBid(int amount)
{
    if (root == nullptr)
    {
        cout << "The auction tree is empty." << endl;
        return;
    }

    bool found = false;
    root = deleteRec(root, amount, found);

    if (found)
    {
        cout << "Bid amount " << amount << " successfully withdrawn/removed." << endl;
    }
    else
    {
        cout << "Bid amount " << amount << " not found in the tree." << endl;
    }
}

void AuctionBST::menu()
{
    int choice, amount;
    do
    {
        cout << "\n--- Auction Site Bid Management --- \n"
             << "1. Insert Bid Amount\n"
             << "2. Print Traversals (Inorder, Preorder, Postorder)\n"
             << "3. Remove a Bid (Bidder Withdraws)\n"
             << "4. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Bid Amount: ";
            cin >> amount;
            insert(amount);
            break;

        case 2:
            printAllTraversals();
            break;

        case 3:
            cout << "Enter Bid Amount to remove: ";
            cin >> amount;
            removeBid(amount);
            cout << "\nTraversals After Removal:";
            printAllTraversals();
            break;

        case 4:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}