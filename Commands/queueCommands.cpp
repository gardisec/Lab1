#include "queueCommands.h"
#include "../Structures/queue.h"

void printQueue(const request& request){
    ifstream file(request.file, ios::in);
    string tempLine;
    fileData setting;
    bool isDone = false;

    if (request.query.size == 1){
        while (getline(file, tempLine)) { // QPRINT
            if (tempLine == " " || tempLine.empty()) {
                continue;
            }
            setting.getInfo(tempLine);
            if (setting.type == "#QUEUE") {
                isDone = true;
                queue<string> currentValue = splitToQueue(setting.data);
                cout << setting.name << ": " << currentValue << endl;
            }
        }
    }
    else if (request.query.size == 2) { // QPRINT name
        string name = request.query[1];
        fileData setting;
        while (getline(file, tempLine)){
            if (tempLine == " " || tempLine.empty()) continue;

            setting.getInfo(tempLine);
            if (setting.name == name && setting.type == "#QUEUE"){
                isDone = true;
                queue<string> currentValue = splitToQueue(setting.data);
                cout << setting.name << ": " << currentValue << endl;
            }
        }
        if (isDone == false){
            throw runtime_error("Incorrect name");
        }
    }
    else {
        throw runtime_error("Incorrect query");
    }
    file.close();
}

void queuePush(const request& request){ //QPUSH name value

    fstream file(request.file, ios::in);
    if (request.query.size != 3){
        throw runtime_error("Incorrect query");
    }
    string name = request.query[1];
    string value = request.query[2];
    string tempLine;
    fileData setting;
    arr<string> buffer;
    bool isDone = false;

    while (getline(file, tempLine)){
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }
        setting.getInfo(tempLine);

        if (setting.name == name && !isDone && setting.type == "#QUEUE"){
            isDone = true;
            queue<string> currentValue = splitToQueue(setting.data);
            currentValue.push(value);
            tempLine = setting.type + ';' + setting.name + ';' + unSplitQueue(currentValue);
            currentValue.clear();
            buffer.push_back(tempLine);
        }
        else {
            buffer.push_back(tempLine);
        }
    }

    if (isDone == false){
        tempLine = "#QUEUE;" + name + ';' + value;
        buffer.push_back(tempLine);
    }
    file.close();
    file.open(request.file, ios::out);

    for (size_t i = 0; i < buffer.size; i++) {
        file << buffer[i] << endl;
    }
    file.close();
}

void queuePop(const request& request){ // QPOP name

    fstream file(request.file, ios::in);

    if (request.query.size != 2) {
        throw runtime_error("Incorrect query");
    }
    string name = request.query[1];
    string tempLine;
    fileData setting;
    arr<string> buffer;
    bool isDone = false;

    while (getline(file, tempLine)){
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }

        setting.getInfo(tempLine);
        if (setting.name == name && !isDone && setting.type == "#QUEUE"){
            isDone = true;
            queue<string> currentValue = splitToQueue(setting.data);
            currentValue.pop();
            tempLine = setting.type + ';' + setting.name + ';' + unSplitQueue(currentValue);
            if (currentValue.head != nullptr){
                buffer.push_back(tempLine);
            }
            currentValue.clear();
        }
        else {
            buffer.push_back(tempLine);
        }
    }
    file.close();
    if (!isDone) {
        throw runtime_error("Incorrect name");
    }
    file.open(request.file, ios::out);

    for (size_t i = 0; i < buffer.size; i++) {
        file << buffer[i] << endl;
    }
    file.close();
}

void queueGet(const request& request){ //QGET name

    ifstream file(request.file, ios::in);
    if (request.query.size != 2) {
        throw runtime_error("Incorrect query");
    }
    string name = request.query[1];
    string tempLine;
    fileData setting;
    bool isDone = false;
    while (getline(file, tempLine)){
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }
        setting.getInfo(tempLine);
        if (setting.name == name && setting.type == "#QUEUE"){
            isDone = true;
            queue<string> currentValue = splitToQueue(setting.data);
            cout << currentValue.getFirst() << endl;
            currentValue.clear();
            break;
        }
    }
    if (!isDone){
        throw runtime_error("Incorrect name");
    }
}