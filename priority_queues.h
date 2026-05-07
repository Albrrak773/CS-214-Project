#ifndef PRIORITY_QUEUES_H
#define PRIORITY_QUEUES_H

#include "iostream"
#include "fstream"
#include "cstring"
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
    void load_pq_from_file();
    void enqueue(int data, int priority);
    int dequeue();
    void display();
    void dump_to_file();
    ~priorityQueue();
};

#endif