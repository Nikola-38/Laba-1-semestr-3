#pragma once
#include <string>
using namespace std;

struct NodeLS {
    int data;
    NodeLS* next;
    NodeLS* previous;
};

void addHeadLS(NodeLS*& head, int value);
void addTailLS(NodeLS*& head, int value);
void deleteHeadLS(NodeLS*& head);
void deleteTailLS(NodeLS*& head);
bool deleteByValueLS(NodeLS*& head, int value);
NodeLS* searchLS(NodeLS* head, int value) ;
void printListLS(NodeLS* head) ;
void clearListLS(NodeLS*& head) ;
void writeToFileLS(NodeLS* head, const string& filename);
void readFromFileLS(NodeLS*& head, const string& filename);

