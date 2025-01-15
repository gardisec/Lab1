#include <iostream>
using namespace std;

// Определение структуры узла бинарного дерева
struct TreeNode {
    int data;
    TreeNode* left;  // Левый ребенок
    TreeNode* right; // Правый ребенок

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Определение структуры для узла двусвязного списка
struct DoublyListNode {
    int data;
    DoublyListNode* prev;
    DoublyListNode* next;

    DoublyListNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// Функция для преобразования бинарного дерева в двусвязный список
void BTtoDLL(TreeNode* root, DoublyListNode*& head, DoublyListNode*& prev) {
    if (!root) return;

    // Рекурсивный вызов для левого поддерева
    BTtoDLL(root->left, head, prev);

    // Преобразование текущего узла дерева в узел списка
    DoublyListNode* current = new DoublyListNode(root->data);
    if (prev == nullptr) {
        // Если это самый левый узел, он становится головой списка
        head = current;
    } else {
        // Связываем текущий узел с предыдущим
        prev->next = current;
        current->prev = prev;
    }
    prev = current; // Обновляем предыдущий узел

    // Рекурсивный вызов для правого поддерева
    BTtoDLL(root->right, head, prev);
}

// Функция для печати двусвязного списка
void printDLL(DoublyListNode* head) {
    DoublyListNode* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    // Пример дерева
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(20);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(25);

    DoublyListNode* head = nullptr; // Голова двусвязного списка
    DoublyListNode* prev = nullptr; // Предыдущий узел

    // Преобразование бинарного дерева в двусвязный список
    BTtoDLL(root, head, prev);

    // Печать двусвязного списка
    cout << "Двусвязный список: ";
    printDLL(head);

    return 0;
}
