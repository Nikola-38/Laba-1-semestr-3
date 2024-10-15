#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NodeLO {
    int data;
    NodeLO* next;
};

// Добавление элемента в голову списка
void addHeadLO(NodeLO*& head, int value) {
    NodeLO* newNodeLO = new NodeLO;
    newNodeLO->data = value;
    newNodeLO->next = head;
    head = newNodeLO;
}

// Добавление элемента в хвост списка
void addTailLO(NodeLO*& head, int value) {
    NodeLO* newNodeLO = new NodeLO;
    newNodeLO->data = value;
    newNodeLO->next = nullptr;

    if (!head) {
        head = newNodeLO;
    } else {
        NodeLO* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNodeLO;
    }
}

// Удаление элемента с головы списка
void deleteHeadLO(NodeLO*& head) {
    if (!head) return;
    NodeLO* temp = head;
    head = head->next;
    delete temp;
}

// Удаление элемента с хвоста списка
void deleteTailLO(NodeLO*& head) {
    if (!head) return;
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    NodeLO* temp = head;
    while (temp->next->next) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

// Удаление элемента по значению
    bool deleteByValueLO(NodeLO*& head, int value) {
        if (!head) return false; // Если список пуст, вернуть false

        // Проверка, нужно ли удалить голову
        if (head->data == value) {
            deleteHeadLO(head); // Предполагается, что deleteHeadLO уже обрабатывает голову
            return true; // Удаление успешно
        }

        NodeLO* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        // Если значение найдено, удалить узел
        if (current->next) {
            NodeLO* temp = current->next;
            current->next = current->next->next;
            delete temp; // Освобождаем память
            return true; // Удаление успешно
        }

        return false; // Значение не найдено
    }


// Поиск элемента по значению
NodeLO* searchLO(NodeLO* head, int value) {
    NodeLO* current = head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Печать списка
void printListLO(NodeLO* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Освобождение памяти
void clearListLO(NodeLO*& head) {
    while (head) {
        deleteHeadLO(head);
    }
}

/// Функция для записи списка в файл
void writeToFileLO(NodeLO* head, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл для записи.\n";
        return;
    }
    NodeLO* temp = head;
    while (temp) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

// Функция для чтения списка из файла
void readFromFileLO(NodeLO*& head, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл для чтения.\n";
        return;
    }

    clearListLO(head); // Очищаем список перед загрузкой новых данных

    int value;
    int count = 0;  // Счетчик прочитанных значений
    while (file >> value) {
        addTailLO(head, value);
        count++;
    }
    if (count > 0) {
        cout << count;
    }
    else {
        cout << "Файл пуст или данные неверны.\n";
    }
    file.close();
}


