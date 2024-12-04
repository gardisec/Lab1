#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Node.h"
#include "ComplTree.h"
using namespace std;

template<typename T>
struct queue{
    Node<T>* head;
    Node<T>* tail;
    int size;

    queue() : head(nullptr), tail(nullptr), size(0) {}

    void push(T val);
    void pop();
    T getFirst();
    void clear();

    friend ostream& operator<<(ostream& os, const queue<T>& que) {
        Node<T>* curr = que.head;
        while (curr != nullptr){
            os << "[" << curr->value << "]";
            if (curr->next != nullptr) {
                os << " -> ";
            }
            curr = curr->next;
        }
        return os;
    }

};


template struct queue<int>;
template struct queue<string>;
template struct queue<TreeNode*>;


queue<string> splitToQueue(const string &input, char delimiter = ' ');
string unSplitQueue(const queue<string>& input, char delimiter = ' ');

#endif // QUEUE_H
