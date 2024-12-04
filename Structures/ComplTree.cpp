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

void Tree :: insertToTree(const string& value) {
    MyQueue<Tree*> que;
    que.push(this);

    while (!que.empty()) {
        Tree* current = que.front();
        que.pop();

        if (!current->left) {
            current->left = new Tree(value);
            return;
        } else {
            que.push(current->left);
        }

        if (!current->right) {
            current->right = new Tree(value);
            return;
        } else {
            que.push(current->right);
        }
    }
}

bool search(const string& value) {
    Tree* root = treeFromString(value);

    if (!root){
        return false;
    }

    MyQueue<Tree*> que;
    que.push(root);

    while (!que.empty()) {
        Tree* current = que.front();
        que.pop();

        if (current->key == value) {
            return true;
        }

        if (current->left){
            que.push(current->left);
        }
        if (current->right) {
            que.push(current->right);
        }
    }
    return false;
}

int maxDepth(Tree* root) {
    if (!root){
        return 0;
    }
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}


int countNodes(Tree* root) {
    if (!root){
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

bool isCompleteBinaryTree(Tree* root) {
    if (!root){
        return true;
    }

    int depth = maxDepth(root);
    int totalNodes = countNodes(root);


    int maxNodes = pow(2, depth) - 1;


    return totalNodes == maxNodes;
}


Tree* treeFromString(const string& input) {

    arr<string> elements = splitToArr(input, ',');

    if (elements.size == 0 || elements[0] == "nullptr"){
        return nullptr;
    }


    auto root = new Tree(elements[0]);
    MyQueue<Tree*> que;
    que.push(root);

    int i = 1;
    while (i < elements.size) {
        Tree* current = que.front();
        que.pop();


        if (i < elements.size && elements[i] != "nullptr") {
            current->left = new Tree(elements[i]);
            que.push(current->left);
        }
        i++;

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
    }

    MyQueue<Tree*> que;
    que.push(root);

    string result;

    while (!que.empty()) {
        Tree* current = que.front();
        que.pop();

        if (current) {
            result += current->key + ",";
            que.push(current->left);
            que.push(current->right);
        } else {
            result += "nullptr,";
        }
    }

    return result;
}

