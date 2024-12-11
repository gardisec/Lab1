#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>
#include "Node.h"

using namespace std;

template<typename T>
struct sList {

    Node<T>* head;

    sList() : head(nullptr) {}

    void headInsert(T value);
    void backInsert(T value);
    void delFirst();
    void delLast();
    void delByVal(T val);
    bool find(T value);

    friend ostream& operator<<(ostream& os, const sList<T>& ls) {
        Node<T> *curr = ls.head;
        os << "{";
        while (curr != nullptr){
            os << "[" << curr->value << "]";
            if (curr->next != nullptr) {
                os << ", ";
            }
            curr = curr->next;
        }
        os << "}";
        return os;
    }

};
sList<string> splitToSList(const string &input);
string unSplitSList(const sList<string>& input);
template struct sList<int>;
template struct sList<string>;

#endif
