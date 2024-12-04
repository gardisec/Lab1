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

    void push(T val){// вставляем в хвост
        Node<T>* newElement = new Node{val};
        if (this->head == nullptr) {
            this->head = newElement;
            this->tail = newElement;
        }
        else {
            this->tail->next = newElement;
            this->tail = newElement;
        }

    }
    void pop(){ //удаляем с головы
        if (this->head == nullptr) return;
        auto tempHead = this->head;
        this->head = this->head->next;
        delete tempHead;
    }
    T front(){
        return this->head->value;
    }

    bool empty(){
        if (this ->head == nullptr){
            return true;
        }else{
            return false;
        }
    }
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


MyQueue<string> splitToQueue(const string &input, char delimiter = ' ');
string unSplitQueue(const MyQueue<string>& input, char delimiter = ' ');

#endif // QUEUE_H
