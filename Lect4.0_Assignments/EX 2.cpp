#include <iostream>

using namespace std;

struct Node {
    int value;
    int priority;
};

class Queue {
private:
    Node queue[100];
    int size;

public:
    Queue() {
        size = 0;
    }

    void enqueue(int value, int priority);
    void dequeue();
    void printQueue();
};

void Queue::enqueue(int value, int priority) {
    int i = size - 1;
    while (i >= 0 && queue[i].priority < priority) {
        queue[i + 1] = queue[i];
        i--;
    }
    queue[i + 1].value = value;
    queue[i + 1].priority = priority;
    size++;
}

void Queue::dequeue() {
    if (size > 0) {
        for (int i = 0; i < size - 1; i++) {
            queue[i] = queue[i + 1];
        }
        size--;
    }
}


void Queue::printQueue() {
    for (int i = 0; i < size; i++) {
        cout << "(" << queue[i].value << ", " << queue[i].priority << ")";
        if (i != size - 1) cout << "; ";
    }
    cout << endl;
}

int main() {
    Queue q;
    int n;
    cin >> n;

    while (n--) {
        string operation;
        cin >> operation;

        if (operation == "enqueue") {
            int x, p;
            cin >> x >> p;
            q.enqueue(x, p);
        } else if (operation == "dequeue") {
            q.dequeue();
        }
    }

    q.printQueue();

    return 0;
}
