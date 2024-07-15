#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <string>

// Task class definition
class Task {
public:
    std::string description;
    Task* next;

    Task(std::string desc);  // Constructor
};

// TaskManager class declaration
class TaskManager {
private:
    Task* head;  // Head of the linked list of tasks
    Task* tail;  // Tail of the linked list

    void loadTasks();  // Load tasks from file
    void saveTasks();  // Save tasks to file

public:
    TaskManager();  // Constructor
    ~TaskManager(); // Destructor

    void addTask(const std::string& desc);  // Add a task
    void deleteTask(const std::string& desc);  // Delete a task
    void listTasks() const;  // List all tasks
};

#endif // TASKMANAGER_H
