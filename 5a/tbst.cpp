#include "tbst.h"

RailwayTBST::RailwayTBST()
{
    head = new node;
    head->ticketNo = -1;
    head->left = head;
    head->right = head;
    head->lbit = false;
    head->rbit = true;
}

void RailwayTBST::insert(int ticketNo)
{
    if (head->left == head)
    {
        node *root = new node;
        root->ticketNo = ticketNo;
        root->left = head;
        root->right = head;
        root->lbit = false;
        root->rbit = false;

        head->left = root;
        head->lbit = true;
        cout << "Ticket number inserted successfully." << endl;
        return;
    }

    node *ptr = head->left;
    node *parent = nullptr;

    while (ptr)
    {
        if (ticketNo == ptr->ticketNo)
        {
            cout << "Ticket number " << ticketNo << " already exists." << endl;
            return;
        }

        parent = ptr;

        if (ticketNo < ptr->ticketNo)
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
    nn->ticketNo = ticketNo;

    if (ticketNo < parent->ticketNo)
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

    cout << "Ticket number " << ticketNo << " inserted successfully." << endl;
}

void RailwayTBST::displayLinks()
{
    if (head->left == head)
    {
        cout << "Counter queue is empty." << endl;
        return;
    }

    node *ptr = head->left;
    while (ptr->lbit)
    {
        ptr = ptr->left;
    }

    cout << "\n--- Node Links & Thread Status ---" << endl;
    while (ptr != head)
    {
        cout << "Ticket: " << ptr->ticketNo << " | ";

        if (ptr->lbit)
            cout << "Left: " << ptr->left->ticketNo << " (Real Child) | ";
        else
            cout << "Left: " << (ptr->left == head ? "HEAD" : to_string(ptr->left->ticketNo)) << " (Thread) | ";

        if (ptr->rbit)
            cout << "Right: " << ptr->right->ticketNo << " (Real Child)" << endl;
        else
            cout << "Right: " << (ptr->right == head ? "HEAD" : to_string(ptr->right->ticketNo)) << " (Thread)" << endl;

        // Inorder traversal step to visit next node
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
    cout << "----------------------------------" << endl;
}

void RailwayTBST::inorderAscending()
{
    if (head->left == head)
    {
        cout << "Counter queue is empty." << endl;
        return;
    }

    node *ptr = head->left;
    while (ptr->lbit)
    {
        ptr = ptr->left;
    }

    cout << "Tickets in Ascending Order: ";
    while (ptr != head)
    {
        cout << ptr->ticketNo << " ";

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
    cout << endl;
}

void RailwayTBST::findSuccessor(int ticketNo)
{
    if (head->left == head)
    {
        cout << "Counter queue is empty." << endl;
        return;
    }

    node *ptr = head->left;
    bool found = false;

    while (ptr != head)
    {
        
        if (ticketNo == ptr->ticketNo)
        {
            found = true;
            break;
        }
        if (ticketNo < ptr->ticketNo)
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

    if (!found)
    {
        cout << "Ticket number " << ticketNo << " not found." << endl;
        return;
    }

    node *succ = nullptr;
    if (!ptr->rbit)
    {
        succ = ptr->right;
    }
    else
    {
        succ = ptr->right;
        while (succ->lbit)
        {
            succ = succ->left;
        }
    }

    if (succ == head)
    {
        cout << "Ticket " << ticketNo << " has no inorder successor (it is the maximum)." << endl;
    }
    else
    {
        cout << "Inorder Successor of Ticket " << ticketNo << " is: " << succ->ticketNo << endl;
    }
}

void RailwayTBST::menu()
{
    int choice, ticketNo;
    do
    {
        cout << "\n--- Railway Counter TBST System ---\n"
             << "1. Insert Ticket Number\n"
             << "2. Print Links & Thread Status for All Nodes\n"
             << "3. Print Tickets in Ascending Order (Inorder, No Stack/Recursion)\n"
             << "4. Find Inorder Successor of a Given Ticket\n"
             << "5. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Ticket Number: ";
            cin >> ticketNo;
            insert(ticketNo);
            break;

        case 2:
            displayLinks();
            break;

        case 3:
            inorderAscending();
            break;

        case 4:
            cout << "Enter Ticket Number to find successor: ";
            cin >> ticketNo;
            findSuccessor(ticketNo);
            break;

        case 5:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}