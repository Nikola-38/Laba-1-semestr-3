#pragma once
#include <iostream>
using namespace std;

struct AVLNode {
    int data;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    int balance = 0;
};

int HeightAVL(AVLNode* root);
void SetBalanceAVL(AVLNode* root);
void TurnRightAVL(AVLNode*& root) ;
void TurnLeftAVL(AVLNode*& root);
void InsertAVL(AVLNode*& root, int key);
bool SearchAVL(AVLNode* root, int key);
AVLNode* MinValueAVLNode(AVLNode* AVLNode);
void DeleteAVLNode(AVLNode*& root, int key);
void InOrderAVL(AVLNode* root);
void PrintTreeAVL(AVLNode* root, int space = 0);
void writeToFileAVL(AVLNode* root, ofstream& file);
void readFromFileAVL(AVLNode*& root, ifstream& file);
void clearAVL(AVLNode*& root);

