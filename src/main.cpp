#include <iostream>
#include "TaskManager.h"

int main() {
    TaskManager manager;
    int choice;
    std::string desc;

    do {
        std::cout << "1. Add Task\n2. Delete Task\n3. List Tasks\n4. Exit\nEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
            case 1:
                std::cout << "Enter task description: ";
                std::getline(std::cin, desc);
                manager.addTask(desc);
                break;
            case 2:
                std::cout << "Enter task description to delete: ";
                std::getline(std::cin, desc);
                manager.deleteTask(desc);
                break;
            case 3:
                manager.listTasks();
                break;
            case 4:
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
