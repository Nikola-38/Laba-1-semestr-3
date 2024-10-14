#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct NodeS {
    string data;
    NodeS* next;
};

struct Stack {
    NodeS* head = nullptr;

};

// Добавление элемента в стек (push)
void pushS(Stack* stack, const string& data) {
    NodeS* new_NodeS = new NodeS{data, nullptr};
    new_NodeS->next = stack->head;
    stack->head = new_NodeS;
}

// Удаление элемента из стека (pop)
string popS(Stack* stack) {
    if (stack->head == nullptr) {
        cout << "Стек пуст!" << endl;
        return ""; // Возвращаем пустую строку, если стек пуст
    }

    NodeS* temp = stack->head;
    string data = temp->data; // Сохраняем данные удаляемого элемента
    stack->head = stack->head->next; // Обновляем голову стека
    delete temp; // Освобождаем память
    return data; // Возвращаем данные
}

// Функция для вывода всех элементов стека
void printStackS(Stack* stack) {
    if (stack->head == nullptr) {
        cout << "Стек пуст!" << endl;
        return;
    }

    NodeS* current = stack->head;
    
    
    // Вывод элементов от верхнего к нижнему
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Освобождение памяти стека
void clearStack(Stack* stack) {
    while (stack->head) {
        popS(stack);
    }
}

// Функция для записи стека в файл
void writeToFileS(const Stack& stack, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл для записи.\n";
        return;
    }
    NodeS* temp = stack.head;
    while (temp) {
        file << temp->data << endl;
        temp = temp->next;
    }
    cout << "Данные успешно записаны в файл.\n";
    file.close();
}


