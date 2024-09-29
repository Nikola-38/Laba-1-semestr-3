#include <iostream>
#include "windows.h"

using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Queue {
    Node* head;
    Node* tail;
};

// Добавление элемента в очередь (push)
void push(Queue& queue, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (!queue.tail) { // Если очередь пустая
        queue.head = newNode;
        queue.tail = newNode;
    } else {
        queue.tail->next = newNode; // Добавляем новый узел в конец
        queue.tail = newNode; // Обновляем указатель на хвост
    }
}

// Удаление элемента из очереди (pop)
int pop(Queue& queue) {
    if (!queue.head) {
        cout << "Очередь пуста!" << endl;
        return -1; // Возвращаем -1, если очередь пуста
    }

    Node* temp = queue.head;
    int value = temp->data;
    queue.head = queue.head->next; // Убираем элемент с головы

    if (!queue.head) { // Если очередь стала пустой
        queue.tail = nullptr;
    }

    delete temp; // Освобождаем память
    return value; // Возвращаем значение удаленного элемента
}

// Чтение (вывод всех элементов очереди)
void printQueue(const Queue& queue) {
    Node* current = queue.head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Освобождение памяти
void clearQueue(Queue& queue) {
    while (queue.head) {
        pop(queue);
    }
}

int main() {
    system("chcp 65001");
    Queue queue;
    queue.head = nullptr; // Инициализация указателей
    queue.tail = nullptr;

    // Добавление элементов
    push(queue, 10);
    push(queue, 20);
    push(queue, 30);

    cout << "Очередь: ";
    printQueue(queue); 

    // Удаление элементов
    cout << "Удаленный элемент: " << pop(queue) << endl; 
    cout << "Очередь после удаления: ";
    printQueue(queue); 

    // Освобождение памяти
    clearQueue(queue);
    return 0;
}
