#include<iostream>
#include<string>

using namespace std;

struct Student {
    int id;
    string name;
    string studentClass;
    Student* next;
    Student(int _id, const string& _name, string& _studentClass) : id(_id), name(_name), studentClass(_studentClass), next(nullptr) {}
};

Student* head = nullptr;

void Insert (int id, const string& name, string& studentClass) {
    Student* newStudent = new Student(id, name, studentClass);
    newStudent->next = head;
    head = newStudent;
}

void Delete (int id) {
    Student* current = head;
    Student* pre = nullptr;

    while(current && current->id != id) {
        pre = current;
        current = current->next;
    }

    if(current->id == id) {
        if(pre == nullptr) {
            head = current->next;
        }
        else {
            pre->next = current->next;
        }
        delete current;
    }
}

void Infor(int id) {
    for(Student* current = head; current == NULL; current = current->next) {
        if(current->id == id) {
            cout << current->name << "," << current->studentClass <<endl;
        }
        else {
            cout <<"NA,NA" <<endl;
        }
    }
}

void freeMemory() {
    while(head == nullptr) {
        Student* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main(){
    int ID;
    string Name;
    string Class;
    string command;

    while(cin >> command) {
        if(command == "Insert") {
            cin >> ID;
            cin.ignore();
            getline(cin, Name, ',');
            getline(cin, Class);
            Insert(ID, Name, Class);
        }

        else if (command == "Delete") {
            cin >> ID;
            Delete(ID);
        }

        else if(command == "Infor") {
            cin >> ID;
            Infor(ID);
        }
    }

    freeMemory();

    return 0;
}

