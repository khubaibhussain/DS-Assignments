#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Patient {
    string name;
    int arrivalOrder;
    string condition;
    int priority;

    Patient(string n, int order, string cond, int pri)
        : name(n), arrivalOrder(order), condition(cond), priority(pri) {}

    bool operator<(const Patient& other) const {
        return (priority == other.priority) ? arrivalOrder > other.arrivalOrder : priority > other.priority;
    }
};

int getPriority(string condition) {
    if (condition == "Heart Attack" || condition == "Stroke") return 1;
    if (condition == "Broken Leg" || condition == "Severe Burn" || condition == "Fractured Arm") return 2;
    if (condition == "Fever" || condition == "Food Poisoning" || condition == "Migraine") return 3;
    return 4;
}

void showQueue(priority_queue<Patient> q) {
    cout << "\nCurrent Treatment Order:\n";
    cout << setw(15) << left << "Patient Name"
         << setw(15) << "Arrival Order"
         << setw(20) << "Emergency Condition"
         << setw(10) << "Priority" << "\n"
         << string(60, '-') << "\n";

    while (!q.empty()) {
        auto p = q.top(); q.pop();
        cout << setw(15) << left << p.name
             << setw(15) << p.arrivalOrder
             << setw(20) << p.condition
             << setw(10) << p.priority << "\n";
    }
    cout << endl;
}

int main() {
    priority_queue<Patient> queue;
    int arrival = 1;

    cout << "=== Hospital Patient Treatment System ===\n";

    while (true) {
        cout << "\nMenu:\n1. Add Patient\n2. Show Current Treatment Order\n3. Exit\nEnter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string name, condition;
            cout << "Enter patient name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter emergency condition: ";
            getline(cin, condition);

            int pri = getPriority(condition);
            queue.push(Patient(name, arrival++, condition, pri));

            cout << "\nPatient added successfully!\n";
            showQueue(queue);
        } 
        else if (choice == 2) {
            showQueue(queue);
        } 
        else if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        } 
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
