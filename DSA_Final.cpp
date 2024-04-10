#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Patient {
    string name;
    int id;
    int priority;

    Patient(string n, int i, int p) : name(n), id(i), priority(p) {}
};

class ClinicManagement {
private:
    vector<Patient> patients;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (patients[parent].priority < patients[index].priority) {
                swap(patients[parent], patients[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < patients.size() && patients[left].priority > patients[largest].priority) {
            largest = left;
        }

        if (right < patients.size() && patients[right].priority > patients[largest].priority) {
            largest = right;
        }

        if (largest != index) {
            swap(patients[index], patients[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insertPatient() {
        string name;
        int id, priority;

        cout << "Enter patient name: ";
        cin >> name;
        cout << "Enter patient ID: ";
        cin >> id;
        cout << "Enter patient priority (1-10): ";
        cin >> priority;

        Patient newPatient(name, id, priority);
        patients.push_back(newPatient);
        heapifyUp(patients.size() - 1);
    }

    void deleteMaxPriorityPatient() {
        if (patients.empty()) {
            cout << "No patients in the system." << endl;
            return;
        }

        swap(patients[0], patients[patients.size() - 1]);
        patients.pop_back();
        heapifyDown(0);
    }

    void printPatients() {
        if (patients.empty()) {
            cout << "No patients in the system." << endl;
            return;
        }

        cout << "Patients in the system:" << endl;
        for (const auto& patient : patients) {
            cout << "Name: " << patient.name << ", ID: " << patient.id << ", Priority: " << patient.priority << endl;
        }
    }
};

int main() {
    ClinicManagement clinic;

    char choice;
    do {
        cout << "1. Add patient\n";
        cout << "2. Delete patient with highest priority\n";
        cout << "3. Display patients\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                clinic.insertPatient();
                break;
            case '2':
                clinic.deleteMaxPriorityPatient();
                break;
            case '3':
                clinic.printPatients();
                break;
            case '4':
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter again.\n";
        }
    } while (choice != '4');

    return 0;
}
