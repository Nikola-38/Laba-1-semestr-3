#include <iostream>
#include <fstream>
#include <iomanip>

#include <string>
using namespace std;

struct AVLNode {
    int data = 0;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    int balance = 0;
};

// Функция для вычисления высоты узла
int HeightAVL(AVLNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return max(HeightAVL(root->left), HeightAVL(root->right)) + 1;
}

// Функция для установки баланса узла
void SetBalanceAVL(AVLNode* root) {
    if (root != nullptr) {
        root->balance = HeightAVL(root->left) - HeightAVL(root->right);
    }
}

// Правый поворот
void TurnRightAVL(AVLNode*& root) {
    AVLNode* leftSubtree = root->left;
    AVLNode* leftSubtreeRightSubtree = leftSubtree->right;

    leftSubtree->right = root;
    root->left = leftSubtreeRightSubtree;

    SetBalanceAVL(root);
    SetBalanceAVL(leftSubtree);

    root = leftSubtree; // Новый корень
}

// Левый поворот
void TurnLeftAVL(AVLNode*& root) {
    AVLNode* rightSubtree = root->right;
    AVLNode* rightSubtreeLeftSubtree = rightSubtree->left;

    rightSubtree->left = root;
    root->right = rightSubtreeLeftSubtree;

    SetBalanceAVL(root);
    SetBalanceAVL(rightSubtree);

    root = rightSubtree; // Новый корень
}

// Вставка узла
void InsertAVL(AVLNode*& root, int key) {
    if (root == nullptr) {
        root = new AVLNode();
        root->data = key;
        return;
    }

    if (key < root->data) {
        InsertAVL(root->left, key);
    }
    else if (key > root->data) {
        InsertAVL(root->right, key);
    }
    else {
        return; // Дубликаты не допускаются
    }

    SetBalanceAVL(root);

    // Балансировка
    if (root->balance > 1) {
        if (key < root->left->data) {
            TurnRightAVL(root); // LL
        }
        else {
            TurnLeftAVL(root->left); // LR
            TurnRightAVL(root);
        }
    }

    if (root->balance < -1) {
        if (key > root->right->data) {
            TurnLeftAVL(root); // RR
        }
        else {
            TurnRightAVL(root->right); // RL
            TurnLeftAVL(root);
        }
    }
}

// Поиск узла
bool SearchAVL(AVLNode* root, int key) {
    while (root) {
        if (key == root->data) {
            return true;
        }
        else if (key < root->data) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return false;
}

// Нахождение узла с минимальным значением

AVLNode* MinValueAVLNode(AVLNode* root) {
    AVLNode* current = root;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

// Удаление узла
void DeleteAVLNode(AVLNode*& root, int key) {
    if (!root) return;

    if (key < root->data) {
        DeleteAVLNode(root->left, key);
    }
    else if (key > root->data) {
        DeleteAVLNode(root->right, key);
    }
    else {
        // Удаление узла
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }
            delete temp;
        }
        else {
            AVLNode* temp = MinValueAVLNode(root->right);
            root->data = temp->data;
            DeleteAVLNode(root->right, temp->data);
        }
    }

    if (!root) return;

    SetBalanceAVL(root);

    // Балансировка
    if (root->balance > 1) {
        if (root->left) { // Проверка на nullptr
            if (root->left->balance >= 0) {
                TurnRightAVL(root); // LL
            }
            else {
                TurnLeftAVL(root->left); // LR
                TurnRightAVL(root);
            }
        }
    }

    if (root->balance < -1) {
        if (root->right) { // Проверка на nullptr
            if (root->right->balance <= 0) {
                TurnLeftAVL(root); // RR
            }
            else {
                TurnRightAVL(root->right); // RL
                TurnLeftAVL(root);
            }
        }
    }
}


// Симметричный обход дерева
void InOrderAVL(AVLNode* root) {
    if (root) {
        InOrderAVL(root->left);
        cout << root->data << " ";
        InOrderAVL(root->right);
    }
}

// Вывод дерева в виде структуры
void PrintTreeAVL(AVLNode* root, int space = 0) {
    if (root == nullptr) return;

    space += 10;

    PrintTreeAVL(root->right, space);

    cout << endl;
    for (int i = 10; i < space; i++) {
        cout << " ";
    }
    cout << root->data << "\n";

    PrintTreeAVL(root->left, space);
}

void writeNodeToFile(AVLNode* node, ofstream& file, int depth) {
    if (!node) return; // Если узел пуст, просто возвращаем

    // Записываем правый узел (если он есть)
    writeNodeToFile(node->right, file, depth + 1);

    // Записываем текущий узел с отступами
    for (int i = 0; i < depth; i++) {
        file << "    "; // Отступы для визуализации уровня
    }
    file << node->data << endl; // Записываем значение узла

    // Записываем левый узел (если он есть)
    writeNodeToFile(node->left, file, depth + 1);
}

// Функция для записи всего дерева в файл
void writeToFileAVL(AVLNode* root, ofstream& file) {
    if (!file) {
        cout << "Не удалось открыть файл для записи.\n";
        return;
    }
    
    // Если дерево пусто, можно записать соответствующее сообщение
    if (!root) {
        file << "Дерево пусто." << endl;
        return;
    }

    writeNodeToFile(root, file, 0); // Начинаем запись с корня
}

// Функция для чтения дерева из файла
void readFromFileAVL(AVLNode*& root, ifstream& file) {
    int value;
    while (file >> value) {
        InsertAVL(root, value);
    }
}

// Функция для очистки дерева
void clearAVL(AVLNode*& root) {
    if (root) {
        clearAVL(root->left);
        clearAVL(root->right);
        delete root;
        root = nullptr;
    }
}


