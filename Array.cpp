#include <iostream>
#include <fstream>
using namespace std;

struct ArrayNode {
    int data;
    ArrayNode* next;
    ArrayNode* previous;
};

// Функция для добавления элемента в конец списка
void appendArray(ArrayNode*& head, int value) {
    ArrayNode* newNode = new ArrayNode;
    if (!newNode) {
        cout << "Ошибка выделения памяти\n";
        return;
    }
    newNode->data = value;
    newNode->next = nullptr;
    newNode->previous = nullptr;

    if (!head) {
        head = newNode;
    } else {
        ArrayNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->previous = temp;
    }
}

int getArray(ArrayNode* head, int index) {
    if (index < 0) {
        cout << "Индекс вне диапазона\n";
        return -1;
    }
    ArrayNode* temp = head;
    for (int i = 0; i < index; i++) {
        if (!temp) {
            cout << "Индекс вне диапазона\n";
            return -1;
        }
        temp = temp->next;
    }
    return temp ? temp->data : -1;
}

bool isValidIndex(ArrayNode* head, int index) {
    if (index < 0) return false;
    ArrayNode* temp = head;
    for (int i = 0; i < index; i++) {
        if (!temp) return false;
        temp = temp->next;
    }
    return true;
}

void removeArray(ArrayNode*& head, int index) {
    if (!isValidIndex(head, index)) {
        cout << "Индекс вне диапазона\n";
        return;
    }

    ArrayNode* temp = head;

    if (index == 0) {
        head = head->next;
        if (head) {
            head->previous = nullptr; // Устанавливаем previous для нового head
        }
        delete temp;
    } else {
        ArrayNode* prev = nullptr;

        for (int i = 0; i < index; i++) {
            prev = temp;
            temp = temp->next;
        }

        if (prev) { // Проверяем, что prev не null
            prev->next = temp->next;
            if (temp->next) {
                temp->next->previous = prev; // Обновляем указатель previous
            }
        }
        delete temp;
    }
}


void replaceArray(ArrayNode* head, int index, int value) {
    if (index < 0) {
        cout << "Индекс вне диапазона\n";
        return;
    }
    ArrayNode* temp = head;
    for (int i = 0; i < index && temp; i++) {
        temp = temp->next;
    }
    if (!temp) {
        cout << "Индекс вне диапазона\n";
        return;
    }
    temp->data = value;
}

int sizeArray(ArrayNode* head) {
    int count = 0;
    ArrayNode* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

void printArray(ArrayNode* head) {
    ArrayNode* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void insertArray(ArrayNode*& head, int index, int value) {
    if (index < 0 || index > sizeArray(head)) {
        cout << "Некорректный индекс.\n";
        return;
    }

    ArrayNode* newNode = new ArrayNode;
    newNode->data = value;

    if (index == 0) {
        newNode->next = head;
        newNode->previous = nullptr;
        if (head) {
            head->previous = newNode;
        }
        head = newNode;
    } else {
        ArrayNode* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->previous = temp;
        if (temp->next) {
            temp->next->previous = newNode;
        }
        temp->next = newNode;
    }
}

void clearArray(ArrayNode*& head) {
    while (head) {
        ArrayNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void writeToFileArray(ArrayNode* head, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл для записи.\n";
        return;
    }
    ArrayNode* temp = head;
    while (temp) {
        file << temp->data << endl;
        temp = temp->next;
    }
    cout << "Данные успешно записаны в файл.\n";
    file.close();
}

void readFromFileArray(ArrayNode*& head, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл для чтения.\n";
        return;
    }

    clearArray(head);

    int value;
    int count = 0;
    while (file >> value) {
        appendArray(head, value);
        count++;
    }
    if (count > 0) {
        cout << count << " значений успешно прочитано из файла.\n";
    } else {
        cout << "Файл пуст или данные неверны.\n";
    }
    file.close();
}

bool containsArray(ArrayNode* head, int value) {
    ArrayNode* temp = head;
    while (temp) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}



