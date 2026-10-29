#include "cinema.h"

CinemaBST::CinemaBST()
{
    root = nullptr;
}

Node* CinemaBST::insertRec(Node* node, int seatNo)
{
    if (node == nullptr)
    {
        return new Node(seatNo);
    }
    if (seatNo < node->seatNo)
    {
        node->left = insertRec(node->left, seatNo);
    }
    else if (seatNo > node->seatNo)
    {
        node->right = insertRec(node->right, seatNo);
    }
    else
    {
        cout << "Seat number " << seatNo << " is already booked." << endl;
    }
    return node;
}

void CinemaBST::insert(int seatNo)
{
    root = insertRec(root, seatNo);
    cout << "Seat number " << seatNo << " booked successfully." << endl;
}

void CinemaBST::checkBooking(int seatNo)
{
    Node* curr = root;
    int comparisons = 0;
    bool found = false;

    while (curr != nullptr)
    {
        comparisons++;
        if (curr->seatNo == seatNo)
        {
            found = true;
            break;
        }
        else if (seatNo < curr->seatNo)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    if (found)
    {
        cout << "Seat " << seatNo << " is ALREADY BOOKED." << endl;
    }
    else
    {
        cout << "Seat " << seatNo << " is NOT booked." << endl;
    }
    cout << "Number of comparisons made: " << comparisons << endl;
}

Node* CinemaBST::findMin(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node* CinemaBST::deleteRec(Node* root, int seatNo, bool &found)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (seatNo < root->seatNo)
    {
        root->left = deleteRec(root->left, seatNo, found);
    }
    else if (seatNo > root->seatNo)
    {
        root->right = deleteRec(root->right, seatNo, found);
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
        root->seatNo = temp->seatNo;
        root->right = deleteRec(root->right, temp->seatNo, found);
    }
    return root;
}

void CinemaBST::inorderRec(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    inorderRec(node->left);
    cout << node->seatNo << " ";
    inorderRec(node->right);
}

void CinemaBST::removeSeat(int seatNo)
{
    if (root == nullptr)
    {
        cout << "Booking tree is empty." << endl;
        return;
    }

    bool found = false;
    root = deleteRec(root, seatNo, found);

    if (found)
    {
        cout << "Booking for seat " << seatNo << " cancelled successfully." << endl;
        cout << "Remaining Booked Seats in Ascending Order: ";
        inorderRec(root);
        cout << endl;
    }
    else
    {
        cout << "Seat number " << seatNo << " was not found in bookings." << endl;
    }
}

void CinemaBST::printParentAndSibling(int seatNo)
{
    if (root == nullptr)
    {
        cout << "Booking tree is empty." << endl;
        return;
    }

    if (root->seatNo == seatNo)
    {
        cout << "Parent: none" << endl;
        cout << "Sibling: none" << endl;
        return;
    }

    Node* curr = root;
    Node* parent = nullptr;

    while (curr != nullptr && curr->seatNo != seatNo)
    {
        parent = curr;
        if (seatNo < curr->seatNo)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    if (curr == nullptr)
    {
        cout << "Seat number " << seatNo << " not found." << endl;
        return;
    }

    // Print Parent
    cout << "Parent: " << (parent != nullptr ? to_string(parent->seatNo) : "none") << endl;

    // Find Sibling
    Node* sibling = nullptr;
    if (parent->left == curr)
    {
        sibling = parent->right;
    }
    else
    {
        sibling = parent->left;
    }

    cout << "Sibling: " << (sibling != nullptr ? to_string(sibling->seatNo) : "none") << endl;
}

void CinemaBST::menu()
{
    int choice, seatNo;
    do
    {
        cout << "\n--- Cinema Seat Booking Management --- \n"
             << "1. Book Seat (Insert)\n"
             << "2. Check Booking Status & Comparisons\n"
             << "3. Cancel Booking (Remove & Print Ascending Order)\n"
             << "4. Print Parent and Sibling of a Seat\n"
             << "5. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Seat Number to book: ";
            cin >> seatNo;
            insert(seatNo);
            break;

        case 2:
            cout << "Enter Seat Number to check: ";
            cin >> seatNo;
            checkBooking(seatNo);
            break;

        case 3:
            cout << "Enter Seat Number to cancel: ";
            cin >> seatNo;
            removeSeat(seatNo);
            break;

        case 4:
            cout << "Enter Seat Number: ";
            cin >> seatNo;
            printParentAndSibling(seatNo);
            break;

        case 5:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}