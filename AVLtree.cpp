#include <iostream>
#include <iomanip> // Для std::setw
using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    int balance = 0;
};

// Функция для вычисления высоты узла
int Height(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

// Функция для установки баланса узла
void SetBalance(Node* root) {
    if (root != nullptr) {
        root->balance = Height(root->left) - Height(root->right);
    }
}

// Правый поворот
void TurnRight(Node*& root) {
    Node* leftSubtree = root->left;
    Node* leftSubtreeRightSubtree = leftSubtree->right;

    leftSubtree->right = root;
    root->left = leftSubtreeRightSubtree;

    SetBalance(root);
    SetBalance(leftSubtree);

    root = leftSubtree; // Новый корень
}

// Левый поворот
void TurnLeft(Node*& root) {
    Node* rightSubtree = root->right;
    Node* rightSubtreeLeftSubtree = rightSubtree->left;

    rightSubtree->left = root;
    root->right = rightSubtreeLeftSubtree;

    SetBalance(root);
    SetBalance(rightSubtree);

    root = rightSubtree; // Новый корень
}

// Вставка узла
void Insert(Node*& root, int key) {
    if (root == nullptr) {
        root = new Node();
        root->data = key;
        return;
    }

    if (key < root->data) {
        Insert(root->left, key);
    } else if (key > root->data) {
        Insert(root->right, key);
    } else {
        return; // Дубликаты не допускаются
    }

    SetBalance(root);

    // Балансировка
    if (root->balance > 1) {
        if (key < root->left->data) {
            TurnRight(root); // LL
        } else {
            TurnLeft(root->left); // LR
            TurnRight(root);
        }
    }

    if (root->balance < -1) {
        if (key > root->right->data) {
            TurnLeft(root); // RR
        } else {
            TurnRight(root->right); // RL
            TurnLeft(root);
        }
    }
}

// Поиск узла
bool Search(Node* root, int key) {
    while (root) {
        if (key == root->data) {
            return true;
        } else if (key < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return false;
}

// Нахождение узла с минимальным значением
Node* MinValueNode(Node* node) {
    Node* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

// Удаление узла
void DeleteNode(Node*& root, int key) {
    if (!root) return;

    if (key < root->data) {
        DeleteNode(root->left, key);
    } else if (key > root->data) {
        DeleteNode(root->right, key);
    } else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = MinValueNode(root->right);
            root->data = temp->data;
            DeleteNode(root->right, temp->data);
        }
    }

    if (!root) return;

    SetBalance(root);

    // Балансировка
    if (root->balance > 1) {
        if (root->left->balance >= 0) {
            TurnRight(root); // LL
        } else {
            TurnLeft(root->left); // LR
            TurnRight(root);
        }
    }

    if (root->balance < -1) {
        if (root->right->balance <= 0) {
            TurnLeft(root); // RR
        } else {
            TurnRight(root->right); // RL
            TurnLeft(root);
        }
    }
}

// Симметричный обход дерева
void InOrder(Node* root) {
    if (root) {
        InOrder(root->left);
        cout << root->data << " ";
        InOrder(root->right);
    }
}

// Вывод дерева в виде структуры
void PrintTree(Node* root, int space = 0) {
    if (root == nullptr) return;

    space += 10;

    PrintTree(root->right, space);

    cout << endl;
    for (int i = 10; i < space; i++) {
        cout << " ";
    }
    cout << root->data << "\n";

    PrintTree(root->left, space);
}

int main() {
    Node* root = nullptr;

    Insert(root, 10);
    Insert(root, 20);
    Insert(root, 30);
    Insert(root, 40);
    Insert(root, 50);
    Insert(root, 25);

    cout << "Inorder traversal of the AVL tree is: ";
    InOrder(root);
    cout << endl;

    cout << "Tree structure:\n";
    PrintTree(root);

    cout << "Deleting 10\n";
    DeleteNode(root, 10);
    cout << "Tree structure after deletion of 10:\n";
    PrintTree(root);
    
    cout << "Searching for 30: " << (Search(root, 30) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100: " << (Search(root, 100) ? "Found" : "Not Found") << endl;

    return 0;
}
