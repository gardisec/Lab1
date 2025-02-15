#include "singleList.h"

template<typename T>
bool sList<T>::find(T value) {
    auto curr = this->head;
    while (curr != nullptr){
        if (curr->value == value) return true;
        curr = curr->next;
    }
    return false;
}

template<typename T>
void sList<T>::delByVal(T val) {
    if (this->head->value == val) delFirst();
    else {
        auto curr = this->head;
        while (curr->next != nullptr && curr->next->value != val){
            curr = curr->next;
        }
        if (curr->next != nullptr) return;
        auto tmp = curr->next;
        curr->next = curr->next->next;
        delete tmp;
    }
}

template<typename T>
void sList<T>::delLast() {
    if (this->head == nullptr) return;
    if (this->head->next == nullptr){
        delete this->head;
        this->head = nullptr;
    }
    else {
        auto ptr = this->head;
        while (ptr->next->next != nullptr){
            ptr = ptr->next;
        }
        delete ptr->next;
        ptr-> next = nullptr;
    }
}

template<typename T>
void sList<T>::delFirst() {
    if (this->head == nullptr) return;
    auto first = this->head;
    this->head = this->head->next;
    delete first;
}

template<typename T>
void sList<T>::backInsert(T value) {
    auto curr = this->head;
    while (curr->next != nullptr){
        curr = curr->next;
    }
    Node<T>* newFirst = new Node(value);
    curr->next = newFirst;
}

template<typename T>
void sList<T>::headInsert(T value) {
    Node<T>* newFirst = new Node(value, this->head);
    this->head = newFirst;
}

sList<string> splitToSList(const string &input){
    string word;
    sList<string> output;
    for (auto ch : input){
        if (ch == ',') {
            output.backInsert(word);
            word = "";
        }
        else{
            word += ch;
        }
    }
    if (word != ""){
        output.backInsert(word);
    }
    return output;
}

string unSplitSList(const sList<string>& input){
    Node<string>* curr = input.head;
    string output;
    while (curr != nullptr){
        output += curr->value + ',';
        curr = curr->next;
    }
    return output;
}