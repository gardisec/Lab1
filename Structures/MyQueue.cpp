#include "MyQueue.h"

template<typename T>
bool MyQueue<T>::empty(){
    if (this ->head == nullptr){
        return true;
    }else{
        return false;
    }
}

template<typename T>
void MyQueue<T>::push(T val) {// вставляем в хвост
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

template<typename T>
void MyQueue<T>::pop() { //удаляем с головы
    if (this->head == nullptr) return;
    auto tempHead = this->head;
    this->head = this->head->next;
    delete tempHead;
}

template<typename T>
T MyQueue<T>::front() {
    return this->head->value;
}

MyQueue<string> splitToQueue(const string &input, char delimiter){
    string word;
    MyQueue<string> output;
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

string unSplitQueue(const MyQueue<string>& input, const char delimiter){
    Node<string>* curr = input.head;
    string output;
    while (curr != nullptr){
        output += curr->value + delimiter;
        curr = curr->next;
    }
    return output;
}