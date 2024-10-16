#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include "array.h"
#include "AVL.h"
#include "Hash.h"
#include "LO.h"
#include "LS.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

void handleArrayCommands(Array& arr) {
    string command;
    while (true) {
        cout << ">> ";
        cin >> command;

        if (command == "APPEND") {
            int value;
            cin >> value;
            // Проверяем, существует ли значение, пройдя по массиву
            bool exists = false;
            for (int i = 0; i < arr.size; ++i) {
                if (arr.data[i] == value) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                Aappend(arr, value);
                // writeToFileArray(arr, "ARRAY.txt");
            } else {
                cout << "Значение уже существует." << endl;
            }
        } else if (command == "AINSERT") {
            int index, value;
            cin >> index >> value;
            if (index >= 0 && index <= Alength(arr)) {
                Ainsert(arr, index, value);
                // writeToFileArray(arr, "ARRAY.txt");
            } else {
                cout << "Индекс вне диапазона." << endl;
            }
        } else if (command == "AGET") {
            int index;
            cin >> index;
            if (index >= 0 && index < Alength(arr)) {
                cout << "Элемент по индексу " << index << ": " << Aget(arr, index) << endl;
            } else {
                cout << "Индекс вне диапазона." << endl;
            }
        } else if (command == "AREMOVE") {
            int index;
            cin >> index;
            if (index >= 0 && index < Alength(arr)) {
                Aremove(arr, index);
                // writeToFileArray(arr, "ARRAY.txt");
            } else {
                cout << "Индекс вне диапазона." << endl;
            }
        } else if (command == "AREPLACE") {
            int index, value;
            cin >> index >> value;
            if (index >= 0 && index < Alength(arr)) {
                Areplace(arr, index, value);
                // writeToFileArray(arr, "ARRAY.txt");
            } else {
                cout << "Индекс вне диапазона." << endl;
            }
        } else if (command == "ASIZE") {
            cout << "Длина списка: " << Alength(arr) << endl;
        } else if (command == "PRINT") {
            printArray(arr);
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Неизвестная команда.\n";
        }
    }
}


void handleAVLCommands(AVLNode*& root) {

    string command;
    while (true) {
        cout << ">> ";
        cin >> command;

        if (command == "AVLINSERT") {
            int value;
            cin >> value;
            InsertAVL(root, value);
            ofstream outFile("AVL.txt", ios::trunc);
            writeToFileAVL(root, outFile);
            outFile.close();
        }
        else if (command == "AVLDEL") {
            int value;
            cin >> value;
            DeleteAVLNode(root, value);
            ofstream outFile("AVL.txt", ios::trunc);
            writeToFileAVL(root, outFile);
            outFile.close();
        }
        else if (command == "AVLSEARCH") {
            int value;
            cin >> value;
            if (SearchAVL(root, value)) {
                cout << "Значение " << value << " найдено." << endl;
            }
            else {
                cout << "Значение " << value << " не найдено." << endl;
            }
        }
        else if (command == "AVLHEIGHT") {
            cout << "Высота дерева: " << HeightAVL(root) << endl;
        }
        else if (command == "AVLMIN") {
            AVLNode* minNode = MinValueAVLNode(root);
            if (minNode) {
                cout << "Минимальное значение: " << minNode->data << endl;
            }
            else {
                cout << "Дерево пусто." << endl;
            }
        }
        else if (command == "PRINT") {
            cout << "Дерево:" << endl;
            PrintTreeAVL(root);
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "Неизвестная команда.\n";
        }
    }
}

void handleHashCommands(Hash& hashTable) {

    string command;
    while (true) {
         cout << ">> ";
        cin >> command;

        if (command == "HINSERT") {
            string key, value;

            cin >> key;
            cin >> value;
            hashTable.insertH(key, value);
            hashTable.writeToFileH("Hash.txt");
        }
        else if (command == "HGET") {
            string key;

            cin >> key;
            string result = hashTable.getH(key);
            if (!result.empty()) {
                cout << "Значение: " << result << endl;
            }
            else {
                cout << "Значение не найдено." << endl;
            }
        }
        else if (command == "HREMOVE") {
            string key;
            cin >> key;
            hashTable.removeH(key);
            hashTable.writeToFileH("Hash.txt");
        }
        else if (command == "HPRINT") {
            cout << "Хеш-таблица:" << endl;
            hashTable.printTableH();
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "Неизвестная команда.\n";
        }
    }
}

void handleListONECommands(NodeLO*& list, const string& filename) {
    string command;
    while (true) {
        cout << ">> ";
        cin >> command;

        if (command == "LOADDHEAD") {
            int value;
            cin >> value;
            addHeadLO(list, value);
            writeToFileLO(list, filename);
        }
        else if (command == "LOADDTAIL") {
            int value;
            cin >> value;
            addTailLO(list, value);
            writeToFileLO(list, filename);
        }
        else if (command == "LODELHEAD") {
            if (list) {
                deleteHeadLO(list);
                writeToFileLO(list, filename);
            }
            else {
                cout << "Список пуст." << endl;
            }
        }
        else if (command == "LODELTAIL") {
            if (list) {
                deleteTailLO(list);
                writeToFileLO(list, filename);
            }
            else {
                cout << "Список пуст." << endl;
            }
        }
        else if (command == "LODELVAL") {
            int value;
            cin >> value;
            if (deleteByValueLO(list, value)) {
                writeToFileLO(list, filename);
            }
            else {
                cout << "Значение не найдено." << endl;
            }
        }
        else if (command == "LOSEARCH") {
            int value;
            cin >> value;
            if (searchLO(list, value)) {
                cout << "Значение найдено." << endl;
            }
            else {
                cout << "Значение не найдено." << endl;
            }
        }
        else if (command == "LOPRINT") {
            cout << "Список: ";
            printListLO(list);
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "Неизвестная команда.\n";
        }
    }
}

void handleListSECCommands(NodeLS*& list2, const string& filename) {
    string command;
    while (true) {
        cout << ">> ";
        cin >> command;

        if (command == "LSADDHEAD") {
            int value;
            cin >> value;
            addHeadLS(list2, value);
            writeToFileLS(list2, filename);
        }
        else if (command == "LSADDTAIL") {
            int value;
            cin >> value;
            addTailLS(list2, value);
            writeToFileLS(list2, filename);
        }
        else if (command == "LSDELHEAD") {
            if (list2) {
                deleteHeadLS(list2);
                writeToFileLS(list2, filename);
            }
            else {
                cout << "Список пуст." << endl;
            }
        }
        else if (command == "LSDELTAIL") {
            if (list2) {
                deleteTailLS(list2);
                writeToFileLS(list2, filename);
            }
            else {
                cout << "Список пуст." << endl;
            }
        }
        else if (command == "LSDELVAL") {
            int value;
            cin >> value;
            if (deleteByValueLS(list2, value)) {
                writeToFileLS(list2, filename);
            }
            else {
                cout << "Значение не найдено." << endl;
            }
        }
        else if (command == "LSSEARCH") {
            int value;
            cin >> value;
            if (searchLS(list2, value)) {
                cout << "Значение найдено." << endl;
            }
            else {
                cout << "Значение не найдено." << endl;
            }
        }
        else if (command == "LSPRINT") {
            cout << "Список: ";
            printListLS(list2);
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "Неизвестная команда.\n";
        }
    }
}


void handleStackCommands(Stack& stack) {
    string command;
    while (true) {
        cout << ">> ";
        cin >> command;

        if (command == "SPUSH") {
            string value;
            cin >> value;
            pushS(&stack, value);
            writeToFileS(stack, "STACK.txt");
        }
        else if (command == "SPOP") {
            string value = popS(&stack);
            if (!value.empty()) {
                writeToFileS(stack, "STACK.txt");
            }
            else {
                cout << "Стек пуст." << endl;
            }
        }
        else if (command == "SPRINT") {
            cout << "Стек: ";
            printStackS(&stack);
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "Неизвестная команда.\n";
        }
    }
}

void handleQueueCommands(Queue& queue) {

    string command;
    while (true) {
        cout << ">> ";
        cin >> command;

        if (command == "QPUSH") {
            int value;
            cin >> value;
            pushQ(queue, value);
            writeToFileQ(queue, "QUEUE.txt");
        }
        else if (command == "QPOP") {
            int value = popQ(queue);
            if (value != -1) {
                writeToFileQ(queue, "QUEUE.txt");
            }
            else {
                cout << "Очередь пуста." << endl;
            }
        }
        else if (command == "QPRINT") {
            cout << "Очередь: ";
            printQueue(queue);
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "Неизвестная команда.\n";
        }
    }
}


int main() {
    system("chcp 65001");

    Array arr; // Теперь используем структуру Array вместо указателя
    Ainit(arr, 10); // Инициализация массива с начальной емкостью 10
    AVLNode* root = nullptr;
    Hash hashTable;
    NodeLO* list = nullptr;
    NodeLS* list2 = nullptr;
    Queue queue;
    Stack stack;

    while (true) {
        string command;
        cout << ">> ";
        cin >> command;

        if (command == "ARRAY") {
            handleArrayCommands(arr); // Передаем массив по ссылке
        }
        else if (command == "AVL") {
            handleAVLCommands(root);
        }
        else if (command == "HASH") {
            handleHashCommands(hashTable);
        }
        else if (command == "LO") {
            handleListONECommands(list, "LISTONE.txt");
        }
        else if (command == "LS") {
            handleListSECCommands(list2, "LISTSEC.txt");
        }
        else if (command == "QUEUE") {
            handleQueueCommands(queue);
        }
        else if (command == "STACK") {
            handleStackCommands(stack);
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "Неизвестная команда. Попробуйте снова." << endl;
        }
    }

    // Очистка памяти
    Adestroy(arr); // Освобождаем память массива
    clearAVL(root);
    hashTable.clearH();
    clearListLO(list);
    clearListLS(list2);
    clearQueue(queue);
    clearStack(&stack);

    return 0;
}
