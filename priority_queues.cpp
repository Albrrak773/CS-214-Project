#include "iostream"
#include "fstream"
using namespace std;
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
    void enqueue(int data, int priority);
    int dequeue();
    void display();
    void dump_to_file();
    ~priorityQueue();
};

priorityQueue::priorityQueue(string filename) { head = NULL; this->filename = filename; }

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
    dump_to_file();
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
    dump_to_file();
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
int main() {
    priorityQueue q("queue_dump.txt");
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