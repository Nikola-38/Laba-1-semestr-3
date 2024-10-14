#pragma once
#include <string>
using namespace std;

struct NodeQ {
    int data;
    NodeQ* next;
};

struct Queue {
    NodeQ* head;
    NodeQ* tail;

    Queue() : head(nullptr), tail(nullptr) {}
};

void pushQ(Queue& queue, int value);
int popQ(Queue& queue);
void printQueue(const Queue& queue);
void clearQueue(Queue& queue) ;
void writeToFileQ(const Queue& queue, const string& filename);
void readFromFileQ(Queue& queue, const string& filename);


