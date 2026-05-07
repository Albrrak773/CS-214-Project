#include "iostream"
#include "fstream"
#include "cstring"
using namespace std;

#define CLEAR system("clear")
#define PAUSE                                                               \
    do {                                                                    \
        cout << "\nPress Enter to continue...";                             \
        cin.ignore();                                                       \
        cin.get();                                                          \
    } while (0)
#define PERSISTANCE_FILE "queue_dump.txt"
class priorityQueue {
  private:
    struct node {
        int priority;
        int data;
        node *link;
    } *head;
    string filename;

  public:
    priorityQueue(string filename);
    void load_pq_from_file();
    void enqueue(int data, int priority);
    int dequeue();
    void display();
    void dump_to_file();
    ~priorityQueue();
};

priorityQueue::priorityQueue(string filename) { head = NULL; this->filename = filename; }

void priorityQueue::load_pq_from_file() {
    ifstream file(filename);
    if (!file.is_open()) {
        ofstream create(filename);
        create.close();
        return;
    }
    int data, priority;
    char comma;
    while (file >> data >> comma >> priority) {
        enqueue(data, priority);
    }
    file.close();
}

void priorityQueue::enqueue(int data, int priority) {

    // inti data
    node *temp, *q;
    temp = new node;
    temp->data = data;
    temp->priority = priority;

    // if empty queue or highest priority, insert at head
    if (head == NULL || priority > head->priority) {
        temp->link = head;
        head = temp;

    // if not empty, walk through the list 
    } else {
        q = head;
        // while not at end and next node has higher or equal priority keep going
        while (q->link != NULL && q->link->priority >= priority)
            q = q->link;
        temp->link = q->link;
        q->link = temp;
    }
}

int priorityQueue::dequeue() {
    if (head == NULL) {
        cout << "Queue is empty" << endl;
        return NULL;
    }
    node *temp;
    int item;
    item = head->data;
    temp = head;
    head = head->link;
    delete temp;
    return item;
}

void priorityQueue::display() {
    if (head == NULL) {
        cout << "Queue is empty" << endl;
        return;
    }
    node *p = head;
    while (p != NULL) {
        cout << "(" << p->data << ", p=" << p->priority << ")";
        if (p->link != NULL)
            cout << " -> ";
        p = p->link;
    }
    cout << endl;
}

void priorityQueue::dump_to_file() {
    ofstream file(filename);
    node *p = head;
    while (p != NULL) {
        file << p->data << "," << p->priority << endl;
        p = p->link;
    }
    file.close();
}

priorityQueue::~priorityQueue() {
    if (head == NULL)
        return;
    node *temp;
    while (head != NULL) {
        temp = head;
        head = head->link;
        delete temp;
    }
}
void pq_menu(priorityQueue &pq) {
    int choice = -1;
    int data, priority;

    while (choice != 0) {
        CLEAR;

        cout << "1. Enqueue." << endl;
        cout << "2. Dequeue." << endl;
        cout << "3. Display." << endl;
        cout << "0. Exit." << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            CLEAR;
            cout << "Enter data: ";
            cin >> data;
            cout << "Enter priority: ";
            cin >> priority;
            pq.enqueue(data, priority);
            cout << "Enqueued (" << data << ", p=" << priority << ")" << endl;
            PAUSE;
            break;
        case 2:
            CLEAR;
            data = pq.dequeue();
            if (data != NULL)
                cout << "Dequeued value: " << data << endl;
            PAUSE;
            break;
        case 3:
            CLEAR;
            cout << "Queue values: \n" << endl;
            pq.display();
            PAUSE;
            break;
        case 0:
            pq.dump_to_file();
            return;
        default:
            cout << "Invalid choice, enter another number." << endl;
            PAUSE;
        }
    }
}

int main() {
    priorityQueue pq(PERSISTANCE_FILE);
    pq.load_pq_from_file();
    pq_menu(pq);
    return 0;
}