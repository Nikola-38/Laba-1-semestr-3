#pragma once
#include <iostream>
using namespace std;

struct ArrayNode {
    int data;
    ArrayNode* next;
    ArrayNode* previous;
};

void appendArray(ArrayNode*& head, int value);
void insertArray(ArrayNode*& head, int index, int value);
int getArray(ArrayNode* head, int index);
void removeArray(ArrayNode*& head, int index);
void replaceArray(ArrayNode* head, int index, int value);
int sizeArray(ArrayNode* head);
void printArray(ArrayNode* head);
void clearArray(ArrayNode*& head);
void writeToFileArray(ArrayNode* head, const string& filename);
void readFromFileArray(ArrayNode*& head, const string& filename);
bool containsArray(ArrayNode* head, int value);
