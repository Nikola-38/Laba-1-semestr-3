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
void addHeadLS(NodeLS*& head, int value) {
    NodeLS* newNodeLS = new NodeLS;
    newNodeLS->data = value;
    newNodeLS->next = head;
    newNodeLS->previous = nullptr;

    if (head) {
        head->previous = newNodeLS;
    }
    head = newNodeLS;
}

// Добавление элемента в хвост списка
void addTailLS(NodeLS*& head, int value) {
    NodeLS* newNodeLS = new NodeLS;
    newNodeLS->data = value;
    newNodeLS->next = nullptr;

    if (!head) {
        newNodeLS->previous = nullptr;
        head = newNodeLS;
    } else {
        NodeLS* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNodeLS;
        newNodeLS->previous = temp;
    }
}

// Удаление элемента с головы списка
void deleteHeadLS(NodeLS*& head) {
    if (!head) return;
    NodeLS* temp = head;
    head = head->next;
    if (head) {
        head->previous = nullptr;
    }
    delete temp;
}

// Удаление элемента с хвоста списка
void deleteTailLS(NodeLS*& head) {
    if (!head) return;
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    NodeLS* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->previous->next = nullptr;
    delete temp;
}

// Удаление элемента по значению
bool deleteByValueLS(NodeLS*& head, int value) {
    if (!head) return false;  // Если список пуст, возвращаем false

    if (head->data == value) {
        deleteHeadLS(head);
        return true;  // Если удаляем голову, возвращаем true
    }

    NodeLS* current = head;
    while (current && current->data != value) {
        current = current->next;
    }

    if (current) {
        // Обновляем ссылки на соседние узлы
        if (current->next) {
            current->next->previous = current->previous;
        }
        if (current->previous) {
            current->previous->next = current->next;
        }
        delete current;  // Удаляем узел
        return true;  // Возвращаем true, если значение найдено и удалено
    }

    return false;  // Если значение не найдено, возвращаем false
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
void clearListLS(NodeLS*& head) {
    while (head) {
        deleteHeadLS(head);
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
    cout << "Данные успешно записаны в файл.\n";
    file.close();
}

// Функция для чтения списка из файла
void readFromFileLS(NodeLS*& head, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл для чтения.\n";
        return;
    }

    clearListLS(head); // Очищаем список перед загрузкой новых данных

    int value;
    int count = 0;  // Счетчик прочитанных значений
    while (file >> value) {
        addTailLS(head, value);
        count++;
    }
    if (count > 0) {
        cout << count << " значений успешно прочитано из файла.\n";
    } else {
        cout << "Файл пуст или данные неверны.\n";
    }
    file.close();
}


