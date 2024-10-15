#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NodeQ {
    int data;
    NodeQ* next;
};

struct Queue {
    NodeQ* head;
    NodeQ* tail;

    Queue() : head(nullptr), tail(nullptr) {}
};

// Добавление элемента в очередь (push)
void pushQ(Queue& queue, int value) {
    NodeQ* newNodeQ = new NodeQ;
    newNodeQ->data = value;
    newNodeQ->next = nullptr;

    if (!queue.tail) { // Если очередь пустая
        queue.head = newNodeQ;
        queue.tail = newNodeQ;
    } else {
        queue.tail->next = newNodeQ; // Добавляем новый узел в конец
        queue.tail = newNodeQ; // Обновляем указатель на хвост
    }
}

// Удаление элемента из очереди (pop)
int popQ(Queue& queue) {
    if (!queue.head) {
        cout << "Очередь пуста!" << endl;
        return -1; // Возвращаем -1, если очередь пуста
    }

    NodeQ* temp = queue.head;
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
    NodeQ* current = queue.head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Освобождение памяти
void clearQueue(Queue& queue) {
    while (queue.head) {
        popQ(queue);
    }
}

// Функция для записи очереди в файл
void writeToFileQ(const Queue& queue, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл для записи.\n";
        return;
    }
    NodeQ* temp = queue.head;
    while (temp) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}


// Функция для чтения очереди из файла (не используется в вашем коде, но оставлю для возможного использования)
void readFromFileQ(Queue& queue, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл для чтения.\n";
        return;
    }

    clearQueue(queue); // Очищаем очередь перед загрузкой новых данных

    int value;
    int count = 0;  // Счетчик прочитанных значений
    while (file >> value) {
        pushQ(queue, value); // Используем push для добавления значений
        count++;
    }
    if (count > 0) {
        cout << count;
    } else {
        cout << "Файл пуст или данные неверны.\n";
    }
    file.close();
}


