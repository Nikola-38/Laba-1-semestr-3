#include <iostream>
#include "windows.h"

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* previous;
};

// Добавление элемента в голову списка
void addHead(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    newNode->previous = nullptr;

    if (head) {
        head->previous = newNode;
    }
    head = newNode;
}

// Добавление элемента в хвост списка
void addTail(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (!head) {
        newNode->previous = nullptr;
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->previous = temp;
    }
}

// Удаление элемента с головы списка
void deleteHead(Node*& head) {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    if (head) {
        head->previous = nullptr;
    }
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
    while (temp->next) {
        temp = temp->next;
    }
    temp->previous->next = nullptr;
    delete temp;
}

// Удаление элемента по значению
void deleteByValue(Node*& head, int value) {
    if (!head) return;
    if (head->data == value) {
        deleteHead(head);
        return;
    }
    Node* current = head;
    while (current && current->data != value) {
        current = current->next;
    }
    if (current) {
        if (current->next) {
            current->next->previous = current->previous;
        }
        if (current->previous) {
            current->previous->next = current->next;
        }
        delete current;
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
    Node* doubleList = nullptr;

    // Добавление элементов
    addHead(doubleList, 3);
    addHead(doubleList, 2);
    addTail(doubleList, 4);
    addTail(doubleList, 5);

    cout << "Список: ";
    printList(doubleList); // Ожидается: 2 3 4 5

    // Удаление элементов
    deleteHead(doubleList);
    cout << "После удаления головы: ";
    printList(doubleList); // Ожидается: 3 4 5

    deleteTail(doubleList);
    cout << "После удаления хвоста: ";
    printList(doubleList); // Ожидается: 3 4

    deleteByValue(doubleList, 3);
    cout << "После удаления элемента со значением 3: ";
    printList(doubleList); // Ожидается: 4

    // Поиск элемента
    Node* found = search(doubleList, 4);
    if (found) {
        cout << "Элемент найден: " << found->data << endl; // Ожидается: 4
    } else {
        cout << "Элемент не найден" << endl;
    }

    // Освобождение памяти
    clearList(doubleList);
    return 0;
}
