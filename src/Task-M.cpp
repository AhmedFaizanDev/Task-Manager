#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Task {
public:
    string description;
    Task* next;

    // Constructor to initialize a task with description
    Task(string desc) : description(desc), next(nullptr) {}
};

class TaskManager {
private:
    Task* head;  // Pointer to the head of the linked list
    Task* tail;  // Pointer to the tail of the linked list

    // Method to load tasks from file when initializing
    void loadTasks() {
        ifstream file("tasks.txt");
        string desc;
        while (getline(file, desc)) {
            addTask(desc);
        }
    }

    // Method to save tasks to file before exiting
    void saveTasks() {
        ofstream file("tasks.txt");
        Task* current = head;
        while (current) {
            file << current->description << endl;
            current = current->next;
        }
    }

public:
    // Constructor to initialize TaskManager and load tasks from file
    TaskManager() : head(nullptr), tail(nullptr) {
        loadTasks();
    }

    // Destructor to save tasks to file and free dynamically allocated memory
    ~TaskManager() {
        saveTasks();
        Task* current = head;
        while (current) {
            Task* next = current->next;
            delete current;
            current = next;
        }
    }

    // Method to add a new task to the end of the list
    void addTask(const string& desc) {
        Task* newTask = new Task(desc);
        if (!head) {
            // If list is empty, newTask becomes both head and tail
            head = newTask;
            tail = newTask;
        } else {
            // Otherwise, append newTask to the end of the list
            tail->next = newTask;
            tail = newTask;
        }
    }

    // Method to delete a task with specified description
    void deleteTask(const string& desc) {
        Task* current = head;
        Task* prev = nullptr;

        while (current) {
            if (current->description == desc) {
                // Found the task to delete
                if (prev) {
                    // If not the head, connect previous node to next node
                    prev->next = current->next;
                } else {
                    // If deleting the head, update head to next node
                    head = current->next;
                }
                if (current == tail) {
                    // If deleting the tail, update tail to previous node
                    tail = prev;
                }
                delete current; // Free memory of deleted node
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Task not found.\n";
    }

    // Method to list all tasks in the manager
    void listTasks() const {
        Task* current = head;
        while (current) {
            cout << current->description << endl;
            current = current->next;
        }
    }
};

int main() {
    TaskManager manager;
    int choice;
    string desc;

    // Main menu loop for task manager interaction
    do {
        cout << "1. Add Task\n2. Delete Task\n3. List Tasks\n4. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                getline(cin, desc);
                manager.addTask(desc);
                break;
            case 2:
                cout << "Enter task description to delete: ";
                getline(cin, desc);
                manager.deleteTask(desc);
                break;
            case 3:
                manager.listTasks();
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
