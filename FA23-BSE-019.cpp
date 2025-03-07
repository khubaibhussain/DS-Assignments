#include <iostream>
#include <string>
using namespace std;

struct TaskNode {
    int taskID;
    string description;
    int priority;
    TaskNode* next;

    TaskNode(int id, string desc, int prio) : taskID(id), description(desc), priority(prio), next(nullptr) {}
};

class TaskManager {
private:
    TaskNode* head;

public:
    TaskManager() : head(nullptr) {}

    ~TaskManager() {
        while (head) {
            TaskNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addTask(int id, string desc, int priority) {
        TaskNode* newNode = new TaskNode(id, desc, priority);

        if (!head || priority > head->priority) {
            newNode->next = head;
            head = newNode;
        } else {
            TaskNode* current = head;
            while (current->next && current->next->priority >= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        cout << "Task added successfully!" << endl;
    }

    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove!" << endl;
            return;
        }
        TaskNode* temp = head;
        head = head->next;
        cout << "Removed Task - ID: " << temp->taskID << ", Description: " << temp->description << ", Priority: " << temp->priority << endl;
        delete temp;
    }

    void removeTaskByID(int id) {
        if (!head) {
            cout << "No tasks to remove!" << endl;
            return;
        }

        if (head->taskID == id) {
            TaskNode* temp = head;
            head = head->next;
            cout << "Removed Task - ID: " << temp->taskID << ", Description: " << temp->description << ", Priority: " << temp->priority << endl;
            delete temp;
            return;
        }

        TaskNode* current = head;
        while (current->next && current->next->taskID != id) {
            current = current->next;
        }

        if (current->next) {
            TaskNode* temp = current->next;
            current->next = current->next->next;
            cout << "Removed Task - ID: " << temp->taskID << ", Description: " << temp->description << ", Priority: " << temp->priority << endl;
            delete temp;
        } else {
            cout << "Task with ID " << id << " not found!" << endl;
        }
    }

    void viewAllTasks() {
        if (!head) {
            cout << "No tasks available!" << endl;
            return;
        }
        TaskNode* current = head;
        cout << "Tasks List:" << endl;
        while (current) {
            cout << "ID: " << current->taskID << ", Description: " << current->description << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }
};

void displayMenu() {
    cout << "\nTask Management System Menu:" << endl;
    cout << "1. Add a new task" << endl;
    cout << "2. Remove the highest priority task" << endl;
    cout << "3. Remove a task by ID" << endl;
    cout << "4. View all tasks" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    TaskManager taskManager;
    int choice, taskID, priority;
    string description;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> taskID;
                cin.ignore();
                cout << "Enter Task Description: ";
                getline(cin, description);
                cout << "Enter Task Priority: ";
                cin >> priority;
                taskManager.addTask(taskID, description, priority);
                break;
            case 2:
                taskManager.removeHighestPriorityTask();
                break;
            case 3:
                cout << "Enter Task ID to remove: ";
                cin >> taskID;
                taskManager.removeTaskByID(taskID);
                break;
            case 4:
                taskManager.viewAllTasks();
                break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}