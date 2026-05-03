#include "iostream"
using namespace std;
class queue {
  private:
    struct node {
        int data;
        node *link;
    } *head, *tail;

  public:
    queue();
    void enqueue(int item);
    int dequeue();
    void display();
    ~queue();
};

// initializing a data member
queue::queue() { head = tail = NULL; }

void queue::enqueue(int item) {
    node *temp;
    temp = new node;
    temp->data = item;
    temp->link = NULL;
    if (head == NULL) {
        tail = head = temp;
        return;
    }
    tail->link = temp;
    tail = tail->link;
}

int queue::dequeue() {
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

void queue::display() {
    if (head == NULL) {
        cout << "Queue is empty" << endl;
        return;
    }
    // get queue length
    int count = 0;
    node *p = head;
    while (p != NULL) {
        count++;
        p = p->link;
    }

    // add queue elements to array
    int *values = new int[count];
    p = head;
    for (int i = 0; i < count; i++) {
        values[i] = p->data;
        p = p->link;
    }

    // print queue from tail to head "backwards".
    for (int i = count - 1; i >= 0; i--) {
        cout << values[i];
        if (i != 0)
            cout << " -> ";
    }
    delete[] values;
    cout << endl;
}

queue::~queue() {
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
    queue q;
    cout << "enqueing 10..." << endl;
    q.enqueue(10);
    cout << "enqueing 20..." << endl;
    q.enqueue(20);
    cout << "enqueing 30..." << endl;
    q.enqueue(30);
    cout << "Queue: ";
    q.display();
    cout << "Dequeing..." << endl;
    q.dequeue();
    cout << "After dequeue: ";
    q.display();
    return 0;
}