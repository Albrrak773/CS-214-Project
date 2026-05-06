#include "iostream"
using namespace std;
class priorityQueue {
  private:
    struct node {
        int priority;
        int data;
        node *link;
    } *head;

  public:
    priorityQueue();
    void enqueue(int data, int priority);
    int dequeue();
    void display();
    ~priorityQueue();
};

// initializing a data member
priorityQueue::priorityQueue() { head = NULL; }

void priorityQueue::enqueue(int data, int priority) {

    // inti data
    node *temp, *q;
    temp = new node;
    temp->data = data;
    temp->priority = priority;

    // if empty queue add node
    if (head == NULL || priority < head->priority) {
        temp->link = head;
        head = temp;

    // if not empty, walk through the list 
    } else {
        q = head;
        // while not at end and node priority is less than priority keep going
        while (q->link != NULL && q->link->priority <= priority)
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
int main() {
    priorityQueue q;
    cout << "enqueing 10..." << endl;
    q.enqueue(10, 1);
    cout << "enqueing 20..." << endl;
    q.enqueue(20, 0);
    cout << "enqueing 30..." << endl;
    q.enqueue(30, 2);
    cout << "Queue: ";
    q.display();
    cout << "Dequeing..." << endl;
    q.dequeue();
    cout << "After dequeue: ";
    q.display();
    return 0;
}