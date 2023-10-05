#include <iostream>
#include <queue>
using namespace std;

class FlashCard {
  public:
    string front;
    string back;
};

priority_queue<FlashCard> group;

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
      exit(0);
      break;
    default:
      cout << "Invalid option." << endl;
  }
}

void openGroup() {
  // Create group list then select one to open
}

void createGroup() {
  // Create a new word group
}

void displayAllGroups() {
  // print all groups
}

void deleteGroup() {
  // delete a single group
}
