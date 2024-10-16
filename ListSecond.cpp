#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NodeLS {
    int data;
    NodeLS* next;
    NodeLS* previous;
};

// Добавление элемента в голову списка
void addHeadLS(NodeLS*& head, NodeLS*& tail, int value) {
    NodeLS* newNodeLS = new NodeLS;
    newNodeLS->data = value;
    newNodeLS->next = head;
    newNodeLS->previous = nullptr;

    if (head) {
        head->previous = newNodeLS;
    } else {
        tail = newNodeLS; // Если список был пуст, новый узел становится хвостом
    }
    head = newNodeLS;
}

// Добавление элемента в хвост списка
void addTailLS(NodeLS*& head, NodeLS*& tail, int value) {
    NodeLS* newNodeLS = new NodeLS;
    newNodeLS->data = value;
    newNodeLS->next = nullptr;

    if (!head) {
        newNodeLS->previous = nullptr;
        head = newNodeLS;
        tail = newNodeLS; // Если список пуст, новый узел становится и головой, и хвостом
    } else {
        newNodeLS->previous = tail;
        tail->next = newNodeLS;
        tail = newNodeLS; // Обновляем хвост
    }
}

// Удаление элемента с головы списка
void deleteHeadLS(NodeLS*& head, NodeLS*& tail) {
    if (!head) return;
    NodeLS* temp = head;
    head = head->next;
    if (head) {
        head->previous = nullptr;
    } else {
        tail = nullptr; // Если список стал пустым, обнуляем хвост
    }
    delete temp;
}

// Удаление элемента с хвоста списка
void deleteTailLS(NodeLS*& head, NodeLS*& tail) {
    if (!tail) return;
    if (head == tail) {
        delete head; // Если один элемент в списке
        head = nullptr;
        tail = nullptr;
        return;
    }
    NodeLS* temp = tail;
    tail = tail->previous;
    tail->next = nullptr;
    delete temp;
}

// Удаление элемента по значению
bool deleteByValueLS(NodeLS*& head, NodeLS*& tail, int value) {
    if (!head) return false;

    if (head->data == value) {
        deleteHeadLS(head, tail);
        return true;
    }

    NodeLS* current = head;
    while (current && current->data != value) {
        current = current->next;
    }

    if (current) {
        if (current->next) {
            current->next->previous = current->previous;
        } else {
            tail = current->previous; // Обновляем хвост, если удаляем последний элемент
        }
        if (current->previous) {
            current->previous->next = current->next;
        }
        delete current;
        return true;
    }

    return false;
}

// Поиск элемента по значению
NodeLS* searchLS(NodeLS* head, int value) {
    NodeLS* current = head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Печать списка
void printListLS(NodeLS* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Освобождение памяти
void clearListLS(NodeLS*& head, NodeLS*& tail) {
    while (head) {
        deleteHeadLS(head, tail);
    }
}

// Функция для записи списка в файл
void writeToFileLS(NodeLS* head, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл для записи.\n";
        return;
    }
    NodeLS* temp = head;
    while (temp) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

// Функция для чтения списка из файла
void readFromFileLS(NodeLS*& head, NodeLS*& tail, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл для чтения.\n";
        return;
    }

    clearListLS(head, tail); // Очищаем список перед загрузкой новых данных

    int value;
    int count = 0;
    while (file >> value) {
        addTailLS(head, tail, value);
        count++;
    }
    if (count > 0) {
        cout << count << " элементов загружено из файла.\n";
    } else {
        cout << "Файл пуст или данные неверны.\n";
    }
    file.close();
}
