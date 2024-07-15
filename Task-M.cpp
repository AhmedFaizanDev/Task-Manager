#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Task 
{
public:
    string description;
    Task* next;
    Task(string desc) : description(desc), next(nullptr) {}
};

class TaskManager
{
private:
    Task* head;

    void loadTasks() 
    {
        ifstream file("tasks.txt");
        string desc;
        while (getline(file, desc)) 
        {
            addTask(desc);
        }
    }

    void saveTasks() 
    {
        ofstream file("tasks.txt");
        Task* current = head;
        while (current != nullptr) 
        {
            file << current->description << endl;
            current = current->next;
        }
    }

public:
    TaskManager() : head(nullptr) 
    {
        loadTasks();
    }

    ~TaskManager() 
    {
        saveTasks();
        Task* current = head;
        while (current != nullptr) 
        {
            Task* next = current->next;
            delete current;
            current = next;
        }
    }

    void addTask(const string& desc) 
    {
        Task* newTask = new Task(desc);
        if (!head) 
        {
            head = newTask;
        } else 
        {
            Task* current = head;
            while (current->next) 
            {
                current = current->next;
            }
            current->next = newTask;
        }
    }

    void deleteTask(const string& desc) 
    {
        if (!head) return;
        if (head->description == desc) 
        {
            Task* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Task* current = head;
        while (current->next && current->next->description != desc) 
        {
            current = current->next;
        }
        if (current->next) 
        {
            Task* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    void listTasks() const 
    {
        Task* current = head;
        while (current) 
        {
            cout << current->description << endl;
            current = current->next;
        }
    }
};
int main() {
    TaskManager manager;
    int choice;
    string desc;

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