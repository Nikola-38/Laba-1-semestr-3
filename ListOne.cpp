#include <iostream>
#include "windows.h"
using namespace std;

struct Node {
    int data;
    Node* next;
};

// Добавление элемента в голову списка
void addHead(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

// Добавление элемента в хвост списка
void addTail(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Удаление элемента с головы списка
void deleteHead(Node*& head) {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

// Удаление элемента с хвоста списка
void deleteTail(Node*& head) {
    if (!head) return;
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    Node* temp = head;
    while (temp->next->next) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

// Удаление элемента по значению
void deleteByValue(Node*& head, int value) {
    if (!head) return;
    if (head->data == value) {
        deleteHead(head);
        return;
    }
    Node* current = head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }
    if (current->next) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

// Поиск элемента по значению
Node* search(Node* head, int value) {
    Node* current = head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Печать списка
void printList(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Освобождение памяти
void clearList(Node*& head) {
    while (head) {
        deleteHead(head);
    }
}

int main() {
    system("chcp 65001");
    Node* forwardList = nullptr;

    // Добавление элементов
    addHead(forwardList, 3);
    addHead(forwardList, 2);
    addTail(forwardList, 4);
    addTail(forwardList, 5);

    cout << "Список: ";
    printList(forwardList);

    // Удаление элементов
    deleteHead(forwardList);
    cout << "После удаления головы: ";
    printList(forwardList); 

    deleteTail(forwardList);
    cout << "После удаления хвоста: ";
    printList(forwardList); 

    deleteByValue(forwardList, 3);
    cout << "После удаления элемента со значением 3: ";
    printList(forwardList); 

    // Поиск элемента
    Node* found = search(forwardList, 4);
    if (found) {
        cout << "Элемент найден: " << found->data << endl; 
    } else {
        cout << "Элемент не найден" << endl;
    }

    // Освобождение памяти
    clearList(forwardList);
    return 0;
}
