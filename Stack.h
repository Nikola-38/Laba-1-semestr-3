#pragma once 
#include <string>
using namespace std;

struct NodeS {
    string data;
    NodeS* next;
};

struct Stack {
    NodeS* head = nullptr;

};

void pushS(Stack* stack, const string& data);
string popS(Stack* stack);
void printStackS(Stack* stack);
void clearStack(Stack* stack);
void writeToFileS(const Stack& stack, const string& filename);
