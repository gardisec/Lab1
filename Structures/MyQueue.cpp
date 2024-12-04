#include "MyQueue.h"

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