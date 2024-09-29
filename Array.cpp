#include <iostream>
#include "windows.h"
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* previous;
};

// Функция для добавления элемента в конец списка
void append(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->previous = nullptr;

    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->previous = temp; // Устанавливаем указатель на предыдущий элемент
    }
}

// Функция для добавления элемента по индексу
void insert(Node*& head, int index, int value) {
    if (index < 0) {
        cout << "Индекс вне диапазона\n";
        return;
    }
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->previous = nullptr;

    if (index == 0) {
        newNode->next = head;
        if (head) {
            head->previous = newNode; // Устанавливаем указатель на предыдущий элемент
        }
        head = newNode;
    } else {
        Node* temp = head;
        for (int i = 0; i < index - 1 && temp; i++) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "Индекс вне диапазона\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->previous = temp; // Устанавливаем указатель на предыдущий элемент
        if (temp->next) {
            temp->next->previous = newNode; // Устанавливаем указатель на предыдущий элемент для следующего узла
        }
        temp->next = newNode;
    }
}

// Функция для получения элемента по индексу
int get(Node* head, int index) {
    if (index < 0) {
        cout << "Индекс вне диапазона\n";
        return -1;
    }
    Node* temp = head;
    for (int i = 0; i < index && temp; i++) {
        temp = temp->next;
    }
    if (!temp) {
        cout << "Индекс вне диапазона\n";
        return -1;
    }
    return temp->data;
}

// Функция для удаления элемента по индексу
void remove(Node*& head, int index) {
    if (index < 0 || !head) {
        cout << "Индекс вне диапазона\n";
        return;
    }
    Node* temp = head;
    if (index == 0) {
        head = head->next;
        if (head) {
            head->previous = nullptr; // Обновляем указатель на предыдущий элемент
        }
        delete temp;
    } else {
        Node* prev = nullptr;
        for (int i = 0; i < index && temp; i++) {
            prev = temp;
            temp = temp->next;
        }
        if (!temp) {
            cout << "Индекс вне диапазона\n";
            return;
        }
        prev->next = temp->next;
        if (temp->next) {
            temp->next->previous = prev; // Обновляем указатель на предыдущий элемент для следующего узла
        }
        delete temp;
    }
}

// Функция для замены элемента по индексу
void replace(Node* head, int index, int value) {
    if (index < 0) {
        cout << "Индекс вне диапазона\n";
        return;
    }
    Node* temp = head;
    for (int i = 0; i < index && temp; i++) {
        temp = temp->next;
    }
    if (!temp) {
        cout << "Индекс вне диапазона\n";
        return;
    }
    temp->data = value;
}

// Функция для получения длины списка
int size(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Функция для чтения списка
void print(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Функция для освобождения памяти
void clear(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    system("chcp 65001");
    Node* arr = nullptr;

    append(arr, 1);
    append(arr, 2);
    append(arr, 3);
    insert(arr, 1, 4); // Вставка 4 по индексу 1
    print(arr); 

    replace(arr, 2, 5); // Замена элемента по индексу 2 на 5
    print(arr); 

    remove(arr, 1); // Удаление элемента по индексу 1
    print(arr); 
    cout << "Длина списка: " << size(arr) << endl; // Ожидается: 3

    // Получение элемента по индексу
    int indexToGet = 1;
    int value = get(arr, indexToGet);
    if (value != -1) {
        cout << "Элемент по индексу " << indexToGet << ": " << value << endl; 
    }

    clear(arr); // Освобождение памяти
    return 0;
}


