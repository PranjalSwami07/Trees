#include "tbst.h"

tbst::tbst() {
  head = new node;
  head->id = -1;
  head->title = "";
  head->left = head;
  head->right = head;
  head->lbit = false;
  head->rbit = true;
}

void tbst::insert(int id, string title) {
  if (head->left == head) {
    node *root = new node;
    root->id = id;
    root->title = title;
    root->left = head;
    root->right = head;
    root->lbit = false;
    root->rbit = false;

    head->left = root;
    head->lbit = true;
    cout << "Book inserted successfully." << endl;
    return;
  }

  node *ptr = head->left;
  node *parent = nullptr;

  while (ptr) {
    if (id == ptr->id) {
      cout << "Book ID " << id << " already exists." << endl;
      return;
    }

    parent = ptr;

    if (id < ptr->id) {
      if (ptr->lbit) {
        ptr = ptr->left;
      } else {
        break;
      }
    } else {
      if (ptr->rbit) {
        ptr = ptr->right;
      } else {
        break;
      }
    }
  }

  node *nn = new node;
  nn->id = id;
  nn->title = title;

  if (id < parent->id) {
    nn->left = parent->left;
    nn->lbit = false;
    nn->right = parent;
    nn->rbit = false;

    parent->left = nn;
    parent->lbit = true;
  } else {
    nn->right = parent->right;
    nn->rbit = false;
    nn->left = parent;
    nn->lbit = false;

    parent->right = nn;
    parent->rbit = true;
  }

  cout << "Book '" << title << "' inserted." << endl;
}

void tbst::inorder() {
  if (head->left == head) {
    cout << "Library index is empty." << endl;
    return;
  }

  node *ptr = head->left;
  while (ptr->lbit) {
    ptr = ptr->left;
  }

  cout << "Book ID\tTitle" << endl;
  while (ptr != head) {
    cout << ptr->id << "\t" << ptr->title << endl;

    if (ptr->rbit) {
      ptr = ptr->right;
      while (ptr->lbit) {
        ptr = ptr->left;
      }
    } else {
      ptr = ptr->right;
    }
  }
}

void tbst::search(int id) {
  if (head->left == head) {
    cout << "Library index is empty." << endl;
    return;
  }

  node *ptr = head->left;
  while (ptr != head) {
    if (id == ptr->id) {
      cout << "Found: " << ptr->id << "\t" << ptr->title << endl;
      return;
    }

    if (id < ptr->id) {
      if (ptr->lbit) {
        ptr = ptr->left;
      } else {
        break;
      }
    } else {
      if (ptr->rbit) {
        ptr = ptr->right;
      } else {
        break;
      }
    }
  }

  cout << "Book ID " << id << " not found." << endl;
}

void tbst::levelOrder() {
  if (head->left == head) {
    cout << "Library index is empty." << endl;
    return;
  }

  node *queue[100];
  int front = 0, rear = 0;

  queue[rear++] = head->left;

  cout << "--- Level Order Traversal ---" << endl;
  while (front < rear) {
    node *curr = queue[front++];
    cout << "ID: " << curr->id << " | Title: " << curr->title << endl;

    if (curr->lbit && curr->left != head) {
      queue[rear++] = curr->left;
    }
    if (curr->rbit && curr->right != head) {
      queue[rear++] = curr->right;
    }
  }
  cout << "-----------------------------" << endl;
}

void tbst::removeBook(int id) {
  if (head->left == head) {
    cout << "Library index is empty." << endl;
    return;
  }

  node *parent = nullptr;
  node *curr = head->left;
  bool found = false;

  while (curr != head) {
    if (id == curr->id) {
      found = true;
      break;
    }
    parent = curr;
    if (id < curr->id) {
      if (curr->lbit)
        curr = curr->left;
      else
        break;
    } else {
      if (curr->rbit)
        curr = curr->right;
      else
        break;
    }
  }

  if (!found) {
    cout << "Book ID " << id << " not found for removal." << endl;
    return;
  }

  // Case: Node with 2 children -> Use Inorder Successor
  if (curr->lbit && curr->rbit) {
    node *succParent = curr;
    node *succ = curr->right;
    while (succ->lbit) {
      succParent = succ;
      succ = succ->left;
    }

    curr->id = succ->id;
    curr->title = succ->title;

    curr = succ;
    parent = succParent;
  }

  // Case: Node with 0 or 1 child
  if (curr == head->left) {
    if (!curr->lbit && !curr->rbit) {
      head->left = head;
      head->lbit = false;
    } else if (curr->lbit && !curr->rbit) {
      node *rightMost = curr->left;
      while (rightMost->rbit)
        rightMost = rightMost->right;
      rightMost->right = head;
      rightMost->rbit = false;
      head->left = curr->left;
    } else if (!curr->lbit && curr->rbit) {
      node *leftMost = curr->right;
      while (leftMost->lbit)
        leftMost = leftMost->left;
      leftMost->left = head;
      leftMost->lbit = false;
      head->left = curr->right;
    }
  } else {
    if (curr == parent->left) {
      if (!curr->lbit && !curr->rbit) {
        parent->left = curr->left;
        parent->lbit = false;
      } else if (curr->lbit && !curr->rbit) {
        node *rightMost = curr->left;
        while (rightMost->rbit)
          rightMost = rightMost->right;
        rightMost->right = parent;
        parent->left = curr->left;
      } else if (!curr->lbit && curr->rbit) {
        node *leftMost = curr->right;
        while (leftMost->lbit)
          leftMost = leftMost->left;
        leftMost->left = curr->left;
        parent->left = curr->right;
      }
    } else {
      if (!curr->lbit && !curr->rbit) {
        parent->right = curr->right;
        parent->rbit = false;
      } else if (curr->lbit && !curr->rbit) {
        node *rightMost = curr->left;
        while (rightMost->rbit)
          rightMost = rightMost->right;
        rightMost->right = curr->right;
        parent->right = curr->left;
      } else if (!curr->lbit && curr->rbit) {
        node *leftMost = curr->right;
        while (leftMost->lbit)
          leftMost = leftMost->left;
        leftMost->left = parent;
        parent->right = curr->right;
      }
    }
  }

  delete curr;
  cout << "Book successfully removed." << endl;
}

void tbst::menu() {
  int choice, id;
  string title;

  do {
    cout << "\n--- Library Management System (TBST) ---\n"
         << "1. Insert Book\n"
         << "2. Print Inorder (Ascending Order)\n"
         << "3. Search Book\n"
         << "4. Remove Book (0 or 1 child)\n"
         << "5. Remove Book (2 children using Successor & Print Level-Order "
            "Before/After)\n"
         << "6. Exit\n"
         << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      cout << "Enter Book ID: ";
      cin >> id;
      cin.ignore();
      cout << "Enter Book Title: ";
      getline(cin, title);
      insert(id, title);
      break;

    case 2:
      cout << "\nBook List in Ascending Order:" << endl;
      inorder();
      break;

    case 3:
      cout << "Enter Book ID to search: ";
      cin >> id;
      search(id);
      break;

    case 4:
      cout << "Enter Book ID to remove (0 or 1 child): ";
      cin >> id;
      removeBook(id);
      cout << "\nUpdated Book List in Ascending Order:" << endl;
      inorder();
      break;

    case 5:
      cout << "Enter Book ID to remove (2 children): ";
      cin >> id;
      cout << "\n--- BEFORE REMOVAL ---" << endl;
      levelOrder();
      removeBook(id);
      cout << "\n--- AFTER REMOVAL ---" << endl;
      levelOrder();
      break;

    case 6:
      cout << "Exiting program..." << endl;
      break;

    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  } while (choice != 6);
}