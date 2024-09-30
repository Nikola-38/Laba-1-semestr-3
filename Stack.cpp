#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    Node* next;
};

struct Stack {
    Node* head = nullptr; // Инициализация стека
};

// Добавление элемента в стек (push)
void push(Stack* stack, const string& data) {
    Node* new_node = new Node{data, nullptr};
    new_node->next = stack->head;
    stack->head = new_node;
}

// Удаление элемента из стека (pop)
void pop(Stack* stack) {
    if (stack->head == nullptr) {
        cout << "Стек пуст!" << endl;
        return;
    }

    Node* new_head = stack->head->next;
    delete stack->head;
    stack->head = new_head;
}

// Функция для вывода всех элементов стека
void printStack(Stack* stack) {
    if (stack->head == nullptr) {
        cout << "Стек пуст!" << endl;
        return;
    }

    Node* current = stack->head;
    
    
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
        pop(stack);
    }
}

int main() {
    Stack stack;

    // Пример использования стека
    push(&stack, "Копатыч");
    push(&stack, "Нюша");
    push(&stack, "Шрэк");

    cout << "Все элементы Stack: ";
    printStack(&stack); 

    pop(&stack);
    cout << "Элементы Stack после удаления: ";
    printStack(&stack); 

    clearStack(&stack); // Освобождение памяти
    return 0;
}
