#include "courier.h"

CourierTBST::CourierTBST()
{
    head = new node;
    head->parcelCode = -1;
    head->left = head;
    head->right = head;
    head->lbit = false;
    head->rbit = true;
}

void CourierTBST::insert(int parcelCode)
{
    if (head->left == head)
    {
        node *root = new node;
        root->parcelCode = parcelCode;
        root->left = head;
        root->right = head;
        root->lbit = false;
        root->rbit = false;

        head->left = root;
        head->lbit = true;
        cout << "Parcel code inserted successfully." << endl;
        return;
    }

    node *ptr = head->left;
    node *parent = nullptr;

    while (ptr)
    {
        if (parcelCode == ptr->parcelCode)
        {
            cout << "Parcel code " << parcelCode << " already exists." << endl;
            return;
        }

        parent = ptr;

        if (parcelCode < ptr->parcelCode)
        {
            if (ptr->lbit)
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if (ptr->rbit)
                ptr = ptr->right;
            else
                break;
        }
    }

    node *nn = new node;
    nn->parcelCode = parcelCode;

    if (parcelCode < parent->parcelCode)
    {
        nn->left = parent->left;
        nn->lbit = false;
        nn->right = parent;
        nn->rbit = false;

        parent->left = nn;
        parent->lbit = true;
    }
    else
    {
        nn->right = parent->right;
        nn->rbit = false;
        nn->left = parent;
        nn->lbit = false;

        parent->right = nn;
        parent->rbit = true;
    }

    cout << "Parcel code " << parcelCode << " inserted successfully." << endl;
}

void CourierTBST::countThreads()
{
    if (head->left == head)
    {
        cout << "Total number of threads in the tree: 0" << endl;
        return;
    }

    int threadCount = 0;
    node *ptr = head->left;
    while (ptr->lbit)
    {
        ptr = ptr->left;
    }

    while (ptr != head)
    {
        if (!ptr->lbit)
            threadCount++;
        if (!ptr->rbit)
            threadCount++;

        if (ptr->rbit)
        {
            ptr = ptr->right;
            while (ptr->lbit)
                ptr = ptr->left;
        }
        else
        {
            ptr = ptr->right;
        }
    }

    cout << "Total number of threads in the tree: " << threadCount << endl;
}

void CourierTBST::preorder()
{
    if (head->left == head)
    {
        cout << "Tree is empty." << endl;
        return;
    }

    cout << "Preorder Traversal: ";
    node *curr = head->left;

    while (curr != head)
    {
        cout << curr->parcelCode << " ";

        if (curr->lbit)
        {
            curr = curr->left;
        }
        else if (curr->rbit)
        {
            curr = curr->right;
        }
        else
        {
            while (curr != head && !curr->rbit)
            {
                curr = curr->right;
            }
            if (curr != head)
            {
                curr = curr->right;
            }
        }
    }
    cout << endl;
}

void CourierTBST::menu()
{
    int choice, parcelCode;
    do
    {
        cout << "\n--- Courier Centre TBST Management ---\n"
             << "1. Insert Parcel Code\n"
             << "2. Count Total Threads\n"
             << "3. Print Preorder Traversal (No Stack/Recursion)\n"
             << "4. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Parcel Code: ";
            cin >> parcelCode;
            insert(parcelCode);
            break;

        case 2:
            countThreads();
            break;

        case 3:
            preorder();
            break;

        case 4:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}