#include <iostream>

using namespace std;

// Структура для хранения ключа и значения
struct Node {
    string key;
    string value;
    Node* next; // Указатель на следующий элемент в цепочке
};


// Хеш-функция
int hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch; // Суммируем ASCII значения символов
    }
    return hash % tableSize; // Возвращаем индекс в пределах размера таблицы
}

    // Добавление элемента
void insert(Node* table[], int tableSize, const string& key, const string& value) {
    int index = hashFunction(key, tableSize);
    Node* newNode = new Node{key, value, nullptr};

    if (!table[index]) {
        table[index] = newNode; // Если ячейка пуста, добавляем новый узел
    } else {
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                current->value = value; // Обновляем значение, если ключ уже существует
                delete newNode; // Удаляем временный узел
                return;
            }
            if (!current->next) {
                current->next = newNode; // Добавляем новый узел в конец цепочки
                return;
            }
            current = current->next;
        }
    }
}

// Получение значения по ключу
string get(Node* table[], int tableSize, const string& key) {
    int index = hashFunction(key, tableSize);
    Node* current = table[index];
    while (current) {
        if (current->key == key) {
            return current->value; // Возвращаем значение, если ключ найден
        }
        current = current->next;
    }
    return "Ключ не найден"; // Если ключ не найден
}

// Удаление элемента по ключу
void remove(Node* table[], int tableSize, const string& key) {
    int index = hashFunction(key, tableSize);
    Node* current = table[index];
    Node* previous = nullptr;

    while (current) {
        if (current->key == key) {
            if (previous) {
                previous->next = current->next; // Удаляем узел из цепочки
            } else {
                table[index] = current->next; // Если это первый узел
            }
            delete current; // Освобождаем память
            return;
        }
        previous = current;
        current = current->next;
    }
    cout << "Ключ не найден для удаления" << endl; // Если ключ не найден
}

// Вывод всех элементов хеш-таблицы
void printTable(Node* table[], int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        if (table[i]) {
            cout << "Индекс " << i << ": ";
            Node* current = table[i];
            while (current) {
                cout << "{" << current->key << ": " << current->value << "} ";
                current = current->next;
            }
            cout << endl;
        }
    }
}

// Освобождение памяти вручную (если требуется)
void clear(Node* table[], int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        Node* current = table[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp; // Освобождаем память
        }
        table[i] = nullptr; // Обнуляем указатели
    }
}
};

int main() {
    const int tableSize = 10;
    Node* hashTable[tableSize] = { nullptr }; // Инициализация хеш-таблицы

 // Пример использования хеш-таблицы
    insert(hashTable, tableSize, "apple", "fruit");
    insert(hashTable, tableSize, "carrot", "vegetable");
    insert(hashTable, tableSize, "banana", "fruit");
    insert(hashTable, tableSize, "broccoli", "vegetable");
    insert(hashTable, tableSize, "apple", "green fruit"); // Обновление значения

    cout << "Получение значения по ключу 'apple': " << get(hashTable, tableSize, "apple") << endl; // Ожидается: green fruit
    cout << "Получение значения по ключу 'carrot': " << get(hashTable, tableSize, "carrot") << endl; // Ожидается: vegetable

    cout << "Содержимое хеш-таблицы:" << endl;
    printTable(hashTable, tableSize);

    remove(hashTable, tableSize, "banana");
    cout << "Содержимое хеш-таблицы после удаления 'banana':" << endl;
    printTable(hashTable, tableSize);

    // Освобождение памяти вручную
    clear(hashTable, tableSize);

    return 0;
}
