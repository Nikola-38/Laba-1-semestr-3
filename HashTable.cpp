#include <iostream>

using namespace std;

// Структура для хранения ключа и значения
struct Node {
    string key;
    string value;
    Node* next; // Указатель на следующий элемент в цепочке
};

// Структура для хеш-таблицы
struct Hash {
    static const int tableSize = 10; // Размер таблицы
    Node* table[tableSize]; // Массив указателей на Node

    // Конструктор
    Hash() {
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr; // Инициализируем массив нулями
        }
    }

    // Хеш-функция
    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash += ch; // Суммируем ASCII значения символов
        }
        return hash % tableSize; // Возвращаем индекс в пределах размера таблицы
    }

    // Добавление элемента
    void insert(const string& key, const string& value) {
        int index = hashFunction(key);
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
    string get(const string& key) {
        int index = hashFunction(key);
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
    void remove(const string& key) {
        int index = hashFunction(key);
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
    void printTable() {
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
    void clear() {
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
    Hash hashTable;

    // Пример использования хеш-таблицы
    hashTable.insert("apple", "fruit");
    hashTable.insert("carrot", "vegetable");
    hashTable.insert("banana", "fruit");
    hashTable.insert("broccoli", "vegetable");
    hashTable.insert("apple", "green fruit"); // Обновление значения

    cout << "Получение значения по ключу 'apple': " << hashTable.get("apple") << endl; // Ожидается: green fruit
    cout << "Получение значения по ключу 'carrot': " << hashTable.get("carrot") << endl; // Ожидается: vegetable

    cout << "Содержимое хеш-таблицы:" << endl;
    hashTable.printTable();

    hashTable.remove("banana");
    cout << "Содержимое хеш-таблицы после удаления 'banana':" << endl;
    hashTable.printTable();

    // Освобождение памяти вручную
    hashTable.clear();

    return 0;
}
