#include <iostream>
#include <fstream>
#include <sstream>
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

void handleArrayCommands(ArrayNode*& arr, const string& fileName, const string& query) {
    istringstream iss(query);
    string command;
    iss >> command;

    ofstream outFile(fileName, ios::app); // Открываем файл в режиме добавления

    if (command == "APPEND") {
        int value;
        iss >> value;
        if (!containsArray(arr, value)) {
            appendArray(arr, value);
            writeToFileArray(arr, outFile);
            cout << "Элемент " << value << " добавлен.\n";
        } else {
            cout << "Элемент уже существует.\n";
        }
    } else if (command == "AINSERT") {
        int index, value;
        iss >> index >> value;
        if (index >= 0 && index <= sizeArray(arr)) { // Исправлено: индекс может быть равен размеру
            insertArray(arr, index, value);
            writeToFileArray(arr, outFile);
            cout << "Элемент " << value << " вставлен на индекс " << index << ".\n";
        } else {
            cout << "Некорректный индекс.\n";
        }
    } else if (command == "AREMOVE") {
        int index;
        iss >> index;
        if (index >= 0 && index < sizeArray(arr)) {
            removeArray(arr, index);
            writeToFileArray(arr, outFile);
            cout << "Элемент на индексе " << index << " удален.\n";
        } else {
            cout << "Некорректный индекс.\n";
        }
    } else if (command == "AREPLACE") {
        int index, value;
        iss >> index >> value;
        if (index >= 0 && index < sizeArray(arr)) {
            replaceArray(arr, index, value);
            writeToFileArray(arr, outFile);
            cout << "Элемент на индексе " << index << " заменен на " << value << ".\n";
        } else {
            cout << "Некорректный индекс.\n";
        }
    } else {
        cout << "Неизвестная команда. Пожалуйста, попробуйте снова.\n";
    }

    outFile.close(); // Закрываем файл
}

void handleAVLCommands(AVLNode*& root, const string& fileName, const string& query) {
    istringstream iss(query);
    string command;
    iss >> command;

    ofstream outFile(fileName, ios::app); // Открываем файл для добавления

    if (command == "AVLINSERT") {
        int value;
        iss >> value;
        InsertAVL(root, value);
        writeToFileAVL(root, outFile); // Записываем дерево в файл
        cout << "Элемент " << value << " вставлен.\n";
    } else if (command == "AVLDEL") {
        int value;
        iss >> value;
        DeleteAVLNode(root, value);
        writeToFileAVL(root, outFile); // Записываем дерево в файл
        cout << "Элемент " << value << " удален.\n";
    } else if (command == "AVLSEARCH") {
        int value;
        iss >> value;
        cout << (SearchAVL(root, value) ? "Значение найдено." : "Значение не найдено.") << endl;
    } else if (command == "AVLHEIGHT") {
        cout << "Высота дерева: " << HeightAVL(root) << endl;
    } else if (command == "AVLMIN") {
        AVLNode* minNode = MinValueAVLNode(root);
        cout << (minNode ? "Минимальное значение: " + to_string(minNode->data) : "Дерево пусто.") << endl;
    } else if (command == "PRINT") {
        PrintTreeAVL(root);
    } else {
        cout << "Неизвестная команда.\n";
    }

    outFile.close(); // Закрываем файл
}


void handleHashCommands(Hash& hashTable, const string& fileName, const string& query) {
    istringstream iss(query);
    string command;
    iss >> command;

    ofstream outFile(fileName, ios::app); // Open the file in append mode

    if (command == "HINSERT") {
        string key, value;
        iss >> key >> value;
        hashTable.insertH(key, value);
        hashTable.writeToFileH(outFile); // Write immediately
    } else if (command == "HGET") {
        string key;
        iss >> key;
        string result = hashTable.getH(key);
        cout << (!result.empty() ? "Значение: " + result : "Значение не найдено.") << endl;
    } else if (command == "HREMOVE") {
        string key;
        iss >> key;
        hashTable.removeH(key);
        hashTable.writeToFileH(outFile); // Write immediately
    } else if (command == "HPRINT") {
        hashTable.printTableH();
    } else {
        cout << "Неизвестная команда.\n";
    }

    outFile.close(); // Close the file
}

void handleListONECommands(NodeLO*& list, const string& fileName, const string& query) {
    istringstream iss(query);
    string command;
    iss >> command;

    ofstream outFile(fileName, ios::app); // Open the file in append mode

    if (command == "LOADDHEAD") {
        int value;
        iss >> value;
        addHeadLO(list, value);
        writeToFileLO(list, outFile); // Write immediately
    } else if (command == "LOADDTAIL") {
        int value;
        iss >> value;
        addTailLO(list, value);
        writeToFileLO(list, outFile); // Write immediately
    } else if (command == "LODELHEAD") {
        if (list) {
            deleteHeadLO(list);
            writeToFileLO(list, outFile); // Write immediately
        } else {
            cout << "Список пуст." << endl;
        }
    } else if (command == "LODELTAIL") {
        if (list) {
            deleteTailLO(list);
            writeToFileLO(list, outFile); // Write immediately
        } else {
            cout << "Список пуст." << endl;
        }
    } else if (command == "LODELVAL") {
        int value;
        iss >> value;
        if (deleteByValueLO(list, value)) {
            writeToFileLO(list, outFile); // Write immediately
        } else {
            cout << "Значение не найдено." << endl;
        }
    } else if (command == "LOSEARCH") {
        int value;
        iss >> value;
        cout << (searchLO(list, value) ? "Значение найдено." : "Значение не найдено.") << endl;
    } else if (command == "LOPRINT") {
        printListLO(list);
    } else {
        cout << "Неизвестная команда.\n";
    }

    outFile.close(); // Close the file
}

void handleListSECCommands(NodeLS*& list2, const string& fileName, const string& query) {
    istringstream iss(query);
    string command;
    iss >> command;

    ofstream outFile(fileName, ios::app); // Open the file in append mode

    if (command == "LSADDHEAD") {
        int value;
        iss >> value;
        addHeadLS(list2, value);
        writeToFileLS(list2, outFile); // Write immediately
    } else if (command == "LSADDTAIL") {
        int value;
        iss >> value;
        addTailLS(list2, value);
        writeToFileLS(list2, outFile); // Write immediately
    } else if (command == "LSDELHEAD") {
        if (list2) {
            deleteHeadLS(list2);
            writeToFileLS(list2, outFile); // Write immediately
        } else {
            cout << "Список пуст." << endl;
        }
    } else if (command == "LSDELTAIL") {
        if (list2) {
            deleteTailLS(list2);
            writeToFileLS(list2, outFile); // Write immediately
        } else {
            cout << "Список пуст." << endl;
        }
    } else if (command == "LSDELVAL") {
        int value;
        iss >> value;
        if (deleteByValueLS(list2, value)) {
            writeToFileLS(list2, outFile); // Write immediately
        } else {
            cout << "Значение не найдено." << endl;
        }
    } else if (command == "LSSEARCH") {
        int value;
        iss >> value;
        cout << (searchLS(list2, value) ? "Значение найдено." : "Значение не найдено.") << endl;
    } else if (command == "LSPRINT") {
        printListLS(list2);
    } else {
        cout << "Неизвестная команда.\n";
    }

    outFile.close(); // Close the file
}

void handleStackCommands(Stack& stack, const string& fileName, const string& query) {
    istringstream iss(query);
    string command;
    iss >> command;

    ofstream outFile(fileName, ios::app); // Open the file in append mode

    if (command == "SPUSH") {
        string value;
        iss >> value;
        pushS(&stack, value);
        writeToFileS(stack, outFile); // Write immediately
    } else if (command == "SPOP") {
        string value = popS(&stack);
        if (!value.empty()) {
            cout << "Удаленное значение: " << value << endl;
            writeToFileS(stack, outFile); // Write immediately
        } else {
            cout << "Стек пуст." << endl;
        }
    } else if (command == "SPRINT") {
        printStackS(&stack);
    } else {
        cout << "Неизвестная команда.\n";
    }

    outFile.close(); // Close the file
}

void handleQueueCommands(Queue& queue, const string& fileName, const string& query) {
    istringstream iss(query);
    string command;
    iss >> command;

    ofstream outFile(fileName, ios::app); // Open the file in append mode

    if (command == "QPUSH") {
        int value;
        iss >> value;
        pushQ(queue, value);
        writeToFileQ(queue, outFile); // Write immediately
    } else if (command == "QPOP") {
        int value = popQ(queue);
        if (value != -1) {
            cout << "Удаленное значение: " << value << endl;
            writeToFileQ(queue, outFile); // Write immediately
        } else {
            cout << "Очередь пуста." << endl;
        }
    } else if (command == "QPRINT") {
        printQueue(queue);
    } else {
        cout << "Неизвестная команда.\n";
    }

    outFile.close(); // Close the file
}

int main(int argc, char* argv[]) {
    system("chcp 65001");

    if (argc != 5) {
        cout << "Использование: ./a.exe --file <filename> --query '<команда>'\n";
        return 1;
    }

    string fileName;
    string query;

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--file") {
            fileName = argv[++i];
        } else if (string(argv[i]) == "--query") {
            query = argv[++i];
        }
    }

    ArrayNode* arr = nullptr;
    AVLNode* root = nullptr;
    Hash hashTable;
    NodeLO* list = nullptr;
    NodeLS* list2 = nullptr;
    Queue queue;
    Stack stack;

    if (query.substr(0, 5) == "ARRAY") {
        handleArrayCommands(arr, fileName, query.substr(6));
    } else if (query.substr(0, 3) == "AVL") {
        handleAVLCommands(root, fileName, query.substr(4));
    } else if (query.substr(0, 4) == "HASH") {
        handleHashCommands(hashTable, fileName, query.substr(5));
    } else if (query.substr(0, 2) == "LO") {
        handleListONECommands(list, fileName, query.substr(3));
    } else if (query.substr(0, 2) == "LS") {
        handleListSECCommands(list2, fileName, query.substr(3));
    } else if (query.substr(0, 6) == "QUEUE") {
        handleQueueCommands(queue, fileName, query.substr(7));
    } else if (query.substr(0, 5) == "STACK") {
        handleStackCommands(stack, fileName, query.substr(6));
    } else {
        cout << "Неизвестная команда. Попробуйте снова." << endl;
    }

    // Очистка памяти
    clearArray(arr);
    clearAVL(root);
    hashTable.clearH();
    clearListLO(list);
    clearListLS(list2);
    clearQueue(queue);
    clearStack(&stack);

    return 0;
}
