#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Data Structures
// ***************

class FlashCard {
  public:
    string front;
    string back;
    int weight;
    FlashCard(string front, string back) {
      this->front = front;
      this->back = back;
      this->weight = 0;
    }
    bool operator<(const FlashCard& other) const {
      return weight < other.weight;
    }
    bool operator>(const FlashCard& other) const {
      return weight > other.weight;
    }
};

class PriorityQueue {
    vector<FlashCard> heap;
public:
    void push(FlashCard data) {
        heap.push_back(data);
        int n = heap.size();
        upHeapify(n - 1);
    }
    void pop() {
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        downHeapify(0);
    }
    FlashCard top() {
        return heap[0];
    }
    bool empty() {
        return heap.empty();
    }
    int size() const{
      return heap.size();
    }
private:
    void upHeapify(int i) {
        int parent = (i - 1) / 2;
        if (heap[i] > heap[parent]) {
            swap(heap[i], heap[parent]);
            upHeapify(parent);
        }
    }
    void downHeapify(int i) {
        int child = 2 * i + 1;
        if (child >= heap.size()) return;
        if (heap[child] < heap[child + 1]) child++;
        if (heap[i] < heap[child]) {
            swap(heap[i], heap[child]);
            downHeapify(child);
        }
    }
};

class Stack {
    private:
        vector<FlashCard> stack;
    public:
        void push(FlashCard flashcard) {
            stack.push_back(flashcard);
        }
        bool pop() {
            if (isEmpty()) {
                return false;
            }
            stack.pop_back();
            return true;
        }
        FlashCard peek() {
            return stack.back();
        }
        bool isEmpty() {
            return stack.empty();
        }
        int size() {
            return stack.size();
        }
};


template <typename T>
class queue {
private:
    std::vector<T> queue;
public:
    void push(const T& value) {
        queue.push_back(value);
    }
    void pop() {
        if (!queue.empty()) {
            queue.erase(queue.begin());
        }
    }
    T front() {
        if (!queue.empty()) {
            return queue.front();
        }
        throw std::runtime_error("Queue is empty");
    }
    bool empty() {
        return queue.empty();
    }
    int size() {
        return queue.size();
    }
};


class Group {
  public:
    string name;
    PriorityQueue group;
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

    Group* getGroupByIndex(int index) {
    if (index < 0 || index >= size()) {
            return nullptr;
        }

        Group* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current;
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
Stack record;

// ***************

void mainMenu();
void openGroup();
void createGroup();
void displayAllGroups();
void deleteGroup();

void groupMenu(Group *g);
void addFlashCard(Group *g);
void deleteFlashCard(Group *g);
void randomFlashCard(Group *g);
void displayAllFlashCard(Group *g);

int main(void) {
  mainMenu();
  return 0;
}

// MainMenu functions
// ******************

void mainMenu() {

  while (true) {
    system("clear");
    cout << "Main Menu:" << endl << endl;
    cout << "1. Open a group" << endl;
    cout << "2. Create a group" << endl;
    cout << "3. Display all groups" << endl;
    cout << "4. Delete a group" << endl;
    cout << "5. Exit" << endl << endl;

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
  cout << "~~~~~~~~~~ Open Group ~~~~~~~~~~" << endl << endl;;
  int op;
  group_list.traverse();
  cout << endl << "Enter group number to open (-1 to return): ";
  cin >> op;
  if (op == -1 || op > group_list.size()) return;
  groupMenu(group_list.getGroupByIndex(op-1));
}

// Create a new word group
void createGroup() {
  system("clear");
  cout << "~~~~~~~~~~ Create Group ~~~~~~~~~~" << endl << endl;;
  string name;
  cout << "Enter new group name: ";
  cin >> name;
  group_list.insertAtHead(name);
}

// print all groups
void displayAllGroups() {
  system("clear");
  cout << "~~~~~~~~~~ Display Group ~~~~~~~~~~" << endl << endl;;
  int op;
  group_list.display();
  cout << "Enter to return: ";
  getchar();
  getchar();
}

// delete a single group
void deleteGroup() {
  system("clear");
  cout << "~~~~~~~~~~ Delete Group ~~~~~~~~~~" << endl << endl;;
  int op;
  group_list.traverse();
  cout << "Which one want to delete?(-1 to return): ";
  cin >> op;
  if (op == -1) return;
  group_list.deleteWithIndex(op-1);
}

// ******************


// GroupMenu functions
// *******************

void groupMenu(Group* g) {
  while (true) {
    system("clear");
    cout  << "Group name: " << g->name << endl << endl;

    cout << "Group Menu:" << endl;
    cout << "1. Add a flashcard" << endl;
    cout << "2. Delete a flashcard" << endl;
    cout << "3. Test a random flashcard" << endl;
    cout << "4. Show all flashcard" << endl;
    cout << "5. Exit" << endl << endl;

    // Prompt the user for an option.
    cout << "Select an option: ";
    int choice;
    cin >> choice;

    // Call the corresponding function.
    switch (choice) {
      case 1:
        addFlashCard(g);
        break;
      case 2:
        deleteFlashCard(g);
        break;
      case 3:
        randomFlashCard(g);
        break;
      case 4:
        displayAllFlashCard(g);
        break;
      case 5:
        return;
        break;
      default:
        cout << "Invalid option." << endl;
    }
  }
}

// create new card for group
void addFlashCard(Group *g) {
  system("clear");
  cout << "~~~~~ Add Flashcard in " << g->name << " ~~~~~" << endl << endl;
  int op;
  cout << "1. Create new flashcard" << endl;
  cout << "2. Undo flashcard" << endl;
  cin >> op;
  if (op == 1) {
    string front, rear;
    cout << "Enter front part: ";
    cin >> front;
    cout << "Enter rear part: ";
    cin.ignore();
    getline(cin, rear);
    g->group.push(FlashCard(front, rear));
  }
  else if (op == 2) {
    if (!record.isEmpty()) {
      g->group.push(record.peek());
      record.pop();
    }
    else {
      cout << "nothing to undo!" << endl;
      cout << "Enter to return: ";
      getchar();
      getchar();
    }
  }
}

// delete a card from group
void deleteFlashCard(Group *g) {
  system("clear");
  cout << "~~~~~ Add Flashcard in " << g->name << " ~~~~~" << endl << endl;
  int op, count = 1;
  queue<FlashCard> temp;
  cout << "1. Delete by ID" << endl;
  cout << "2. Delete by word" << endl;
  cin >> op;
  if (op == 1) {
    int id;
    cout << "Enter id: ";
    cin >> id;
    if (id < 1 || id > g->group.size()) {
      cout << "Invalid ID!" << endl;
      cout << "Enter to return: ";
      getchar();
      getchar();
      return;
    }
    else {
      while (!g->group.empty()) {
        FlashCard f = g->group.top();
        if (count == id) {
          g->group.pop();
          record.push(f);
          break;
        }
        temp.push(f);
        g->group.pop();
        count++;
      }
    }
  }
  else if (op == 2) {
    string word;
    bool found = false;
    cout << "Enter the word: ";
    cin >> word;
    while (!g->group.empty()) {
      FlashCard f = g->group.top();
      if (word == f.front) {
        found = true;
        g->group.pop();
        record.push(f);
        break;
      }
      temp.push(f);
      g->group.pop();
    }
    if (!found) {
      cout << "Word not found!" << endl;
      cout << "Enter to return: ";
      getchar();
      getchar();
    }
  }
  else {
    cout << "Inalid option" << endl;
  }
  while (!temp.empty()) {
    g->group.push(temp.front());
    temp.pop();
  }
}

// test a random card based on weight
void randomFlashCard(Group *g) {
  system("clear");
  cout << "~~~~~ Random Flashcard in " << g->name << " ~~~~~" << endl << endl;
  if (g->group.empty()) return;
  string ans;
  FlashCard q = g->group.top();
  g->group.pop();
  cout << "Front: " << q.front << endl;
  cout << "Enter the meanning: ";
  cin.ignore();
  getline(cin, ans);
  if (ans == q.back) {
    cout << "you are correct!" << endl;
    if (q.weight != 0) q.weight -= 1;
  }
  else {
    cout << "you are wrong!" << endl;
    cout << "Correct ans is: " << q.back << endl;
    q.weight += 1;
  }
  g->group.push(q);
  cout << "Enter to return: ";
  getchar();
}

// show front and back of all cards in group
void displayAllFlashCard(Group *g) {
  system("clear");
  cout << "~~~~~ All Flashcards in " << g->name << " ~~~~~" << endl << endl;
  queue<FlashCard> temp;
  while (!g->group.empty()) {
    FlashCard f = g->group.top();
    cout << "Front: " << f.front << endl;
    cout << "Back: " << f.back << endl << endl;
    temp.push(f);
    g->group.pop();
  }
  while (!temp.empty()) {
    g->group.push(temp.front());
    temp.pop();
  }
  int op;
  cout << "Enter to return: ";
  getchar();
  getchar();
}

// *******************

