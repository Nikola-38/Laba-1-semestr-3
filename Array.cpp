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
    newNode->data = value;
    newNode->next = nullptr;
    newNode->previous = nullptr;

    if (!head) {
        head = newNode; // Если список пуст, новый элемент становится первым
    } else {
        ArrayNode* current = head;
        while (current->next) {
            current = current->next; // Находим последний элемент
        }
        current->next = newNode; // Добавляем новый элемент в конец
        newNode->previous = current; // Устанавливаем указатель на предыдущий элемент
    }
}

int getArray(ArrayNode* head, int index) {
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
        for (int i = 0; i < index; i++) {
            temp = temp->next; // Находим элемент по индексу
        }
        if (temp->previous) {
            temp->previous->next = temp->next; // Обновляем указатель следующего элемента
        }
        if (temp->next) {
            temp->next->previous = temp->previous; // Обновляем указатель предыдущего элемента
        }
        delete temp;
    }
}

void replaceArray(ArrayNode* head, int index, int value) {
    if (!isValidIndex(head, index)) {
        cout << "Индекс вне диапазона\n";
        return;
    }
    ArrayNode* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->data = value;
}

int sizeArray(ArrayNode* head) {
    int size = 0;
    ArrayNode* temp = head;
    while (temp) {
        size++;
        temp = temp->next; 
    }
    return size;
}

void printArray(ArrayNode* head) {
    ArrayNode* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Функция для вставки элемента по индексу
void insertArray(ArrayNode*& head, int index, int value) {
    if (index < 0) {
        cout << "Некорректный индекс.\n";
        return;
    }

    ArrayNode* newNode = new ArrayNode;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->previous = nullptr;

    if (index == 0) {
        // Вставка в начало
        newNode->next = head; // Новый элемент указывает на текущий первый элемент
        if (head) {
            head->previous = newNode; // Устанавливаем указатель previous для старого head
        }
        head = newNode; // Новый элемент становится первым
    } else {
        ArrayNode* current = head;
        for (int i = 0; i < index - 1 && current != nullptr; ++i) {
            current = current->next; // Находим элемент перед индексом
        }
        
        if (current != nullptr) {
            // Вставка в середину или конец
            newNode->next = current->next; // Новый элемент указывает на следующий
            if (current->next) {
                current->next->previous = newNode; // Устанавливаем previous для следующего элемента
            }
            current->next = newNode; // Предыдущий указывает на новый элемент
            newNode->previous = current; // Устанавливаем указатель previous для нового элемента
        } else {
            // Если индекс больше размера списка, вставка не производится
            delete newNode; // Удаляем новый элемент, так как вставка не состоялась
            cout << "Некорректный индекс.\n";
        }
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
    }
    else {
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


