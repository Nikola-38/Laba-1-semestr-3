#pragma once
#include <string>
using namespace std;

struct NodeLO {
    int data;
    NodeLO* next;
};

void addHeadLO(NodeLO*& head, int value);
void addTailLO(NodeLO*& head, int value);
void deleteHeadLO(NodeLO*& head) ;
void deleteTailLO(NodeLO*& head);
bool deleteByValueLO(NodeLO*& head, int value);
NodeLO* searchLO(NodeLO* head, int value);
void printListLO(NodeLO* head);
void clearListLO(NodeLO*& head);
void writeToFileLO(NodeLO* head, const string& filename);
void readFromFileLO(NodeLO*& head, const string& filename);


