#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Node.h"
#include "ComplTree.h"


using namespace std;

template<typename T>
struct MyQueue{
    Node<T>* head;
    Node<T>* tail;

    MyQueue() : head(nullptr), tail(nullptr) {}

    void push(T val);
    void pop();
    T front();

    bool empty();
    friend ostream& operator<<(ostream& os, const MyQueue<T>& que) {
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


template struct MyQueue<int>;
template struct MyQueue<string>;
template struct MyQueue<Tree*>;


MyQueue<string> splitToQueue(const string &input, char delimiter = ' ');
string unSplitQueue(const MyQueue<string>& input, char delimiter = ' ');

#endif // QUEUE_H
