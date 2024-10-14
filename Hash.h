#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    string key;
    string value;
    Node* next;
};

class Hash {
public:
    static const int tableSize = 10;
    Node* table[tableSize];

    Hash();
    void insertH(const string& key, const string& value);
    string getH(const string& key);
    void removeH(const string& key);
    void printTableH();
    void writeToFileH(const string& filename);
    void readFromFileH(const string& filename);
    void clearH();

private:
    int hashFunction(const string& key); // Объявление хеш-функции
};
