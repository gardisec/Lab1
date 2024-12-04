#include "queue.h"

template<typename T>
void queue<T>::push(T val) {// вставляем в хвост
    Node<T>* newElement = new Node{val};
    if (this->head == nullptr) {
        this->head = newElement;
        this->tail = newElement;
    }
    else {
        this->tail->next = newElement;
        this->tail = newElement;
    }
    size++;
}

template<typename T>
void queue<T>::pop() { //удаляем с головы
    if (this->head == nullptr) return;
    auto tempHead = this->head;
    this->head = this->head->next;
    delete tempHead;
    size--;
}

template<typename T>
T queue<T>::getFirst() {
    return this->head->value;
}

template<typename T>
void queue<T>::clear() {
    auto temp = this->head;
    while (this->head != nullptr){
        temp = temp->next;
        delete this->head;
        this->head = temp;
    }
}

queue<string> splitToQueue(const string &input, char delimiter){
    string word;
    queue<string> output;
    for (auto ch : input){
        if (ch == delimiter) {
            output.push(word);
            word = "";
        }
        else{
            word += ch;
        }
    }
    if (!word.empty()){
        output.push(word);
    }
    return output;
}

string unSplitQueue(const queue<string>& input, const char delimiter){
    Node<string>* curr = input.head;
    string output;
    while (curr != nullptr){
        output += curr->value + delimiter;
        curr = curr->next;
    }
    return output;
}