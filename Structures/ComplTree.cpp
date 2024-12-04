#include "ComplTree.h"


void Tree ::printTree() {
    if (!this) return;

    MyQueue<Tree*> que;
    que.push(this);

    while (!que.empty()) {
        Tree* current = que.front();
        que.pop();

        cout << current->key << " ";

        if (current->left){
            que.push(current->left);
        }
        if (current->right){
            que.push(current->right);
        }
    }
    cout << endl;
}

// Вставка элемента в бинарное дерево
void Tree :: insertToTree(const string& value) {
    MyQueue<Tree*> que;
    que.push(this); // Начинаем с текущего узла.

    while (!que.empty()) {
        Tree* current = que.front();
        que.pop();

        // Проверяем левый потомок.
        if (!current->left) {
            current->left = new Tree(value);
            return;
        } else {
            que.push(current->left);
        }

        // Проверяем правый потомок.
        if (!current->right) {
            current->right = new Tree(value);
            return;
        } else {
            que.push(current->right);
        }
    }
}

bool search(const string& value) {
    // Преобразуем строку в дерево.
    Tree* root = treeFromString(value);

    // Если дерево пустое, возвращаем false.
    if (!root){
        return false;
    }

    // Выполняем поиск значения в дереве.
    MyQueue<Tree*> que;
    que.push(root);

    while (!que.empty()) {
        Tree* current = que.front();
        que.pop();

        if (current->key == value) {
            return true; // Найдено значение.
        }

        if (current->left){
            que.push(current->left);
        }
        if (current->right) {
            que.push(current->right);
        }
    }
    return false; // Значение не найдено.
}


// Функция для вычисления высоты дерева.
int maxDepth(Tree* root) {
    if (!root){
        return 0;
    }
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// Функция для подсчета всех узлов дерева (не nullptr).
int countNodes(Tree* root) {
    if (!root){
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Проверка, является ли дерево полным бинарным.
bool isCompleteBinaryTree(Tree* root) {
    if (!root){
        return true; // Пустое дерево является полным.
    }

    int depth = maxDepth(root);          // Максимальная глубина дерева.
    int totalNodes = countNodes(root);   // Общее количество узлов.

    // Максимально возможное количество узлов для данной глубины.
    int maxNodes = pow(2, depth) - 1;

    // Дерево полно, если общее количество узлов соответствует \(2^h - 1\).
    return totalNodes == maxNodes;
}


Tree* treeFromString(const string& input) {
    // Разбиваем строку по запятым
    arr<string> elements = splitToArr(input, ',');

    if (elements.size == 0 || elements[0] == "nullptr"){
        return nullptr;
    }

    // Создаем корень дерева
    auto root = new Tree(elements[0]);
    MyQueue<Tree*> que;
    que.push(root);

    int i = 1;
    while (i < elements.size) {
        Tree* current = que.front();
        que.pop();

        // Левый потомок
        if (i < elements.size && elements[i] != "nullptr") {
            current->left = new Tree(elements[i]);
            que.push(current->left);
        }
        i++;

        // Правый потомок
        if (i < elements.size && elements[i] != "nullptr") {
            current->right = new Tree(elements[i]);
            que.push(current->right);
        }
        i++;
    }

    return root;
}

string treeToString(Tree* root) {
    if (!root){
        return "";
    }  // Если дерево пустое, возвращаем пустую строку.

    MyQueue<Tree*> que;
    que.push(root);

    string result;

    while (!que.empty()) {
        Tree* current = que.front();
        que.pop();

        if (current) {
            result += current->key + ","; // Добавляем значение текущего узла.
            que.push(current->left);        // Добавляем левого потомка в очередь.
            que.push(current->right);       // Добавляем правого потомка в очередь.
        } else {
            result += "nullptr,"; // Если узел отсутствует, добавляем "null".
        }
    }

    return result;
}

