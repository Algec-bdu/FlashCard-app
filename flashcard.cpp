#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Data Structures
// ***************

class FlashCard {
  public:
    string front;
    string back;
};

class Group {
  public:
    string name;
    priority_queue<FlashCard> group;
    Group *next;
    Group (string g) {
      this->name = g;
      next = NULL;
    }
};

class GroupList {
private:
    Group* head;

public:
    GroupList() {
        head = nullptr;
    }

    ~GroupList() {
        // Delete all nodes in the linked list.
        Group* current = head;
        while (current != nullptr) {
            Group* next = current->next;
            delete current;
            current = next;
        }
    }

    // Inserts a new group at the head of the linked list.
    void insertAtHead(string group_name) {
        Group* new_node = new Group(group_name);
        new_node->next = head;
        head = new_node;
    }

    // Deletes the group at the specified index.
    void deleteWithIndex(int index) {
        if (index < 0 || index >= size()) {
            cout << "Invalid index." << endl;
            return;
        }

        Group* current = head;
        Group* previous = nullptr;
        for (int i = 0; i < index; i++) {
            previous = current;
            current = current->next;
        }

        if (previous == nullptr) {
            head = head->next;
        } else {
            previous->next = current->next;
        }

        delete current;
    }

    // Traverses the linked list and prints the contents of each group.
    void traverse() {
        int count = 1;
        Group* current = head;
        while (current != nullptr) {
            cout << count++ << ". " << current->name << endl;
            current = current->next;
        }
    }

    void display() {
        int count = 1;
        Group* current = head;
        while (current != nullptr) {
            cout << count++ << ". " << current->name << endl;
            cout << "size: " << current->group.size() << endl << endl;
            current = current->next;
        }
    }

    // Returns the size of the linked list.
    int size() {
        int size = 0;
        Group* current = head;
        while (current != nullptr) {
            size++;
            current = current->next;
        }
        return size;
    }
};

GroupList group_list;

// ***************

void mainMenu();
void openGroup();
void createGroup();
void displayAllGroups();
void deleteGroup();

int main(void) {
  mainMenu();
  return 0;
}

void mainMenu() {

  while (true) {
    system("clear");
    cout << "Main Menu:" << endl;
    cout << "1. Open a group" << endl;
    cout << "2. Create a group" << endl;
    cout << "3. Display all groups" << endl;
    cout << "4. Delete a group" << endl;
    cout << "5. Exit" << endl;

    // Prompt the user for an option.
    cout << "Select an option: ";
    int choice;
    cin >> choice;

    // Call the corresponding function.
    switch (choice) {
      case 1:
        openGroup();
        break;
      case 2:
        createGroup();
        break;
      case 3:
        displayAllGroups();
        break;
      case 4:
        deleteGroup();
        break;
      case 5:
        return;
        break;
      default:
        cout << "Invalid option." << endl;
    }
  }
}

// Create group list then select one to open
void openGroup() {
  system("clear");
  // vector will be replaced with linked list
  int op;
  group_list.traverse();
  cout << endl << "Enter group number to open (-1 to return): ";
  cin >> op;
  if (op == -1) return;
}

// Create a new word group
void createGroup() {
  system("clear");
  string name;
  cout << "Enter new group name: ";
  cin >> name;
  group_list.insertAtHead(name);
}

// print all groups
void displayAllGroups() {
  system("clear");
  int op;
  group_list.display();
  cout << "Enter any number to return: ";
  cin >> op;
}

// delete a single group
void deleteGroup() {
  system("clear");
  int op;
  group_list.traverse();
  cout << "Which one want to delete?(-1 to return): ";
  cin >> op;
  if (op == -1) return;
  group_list.deleteWithIndex(op-1);
}
