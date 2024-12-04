#include "stackCommands.h"
#include "../Structures/Stack.h"

void printStack(const request& request){
    ifstream file(request.file, ios::in);
    string tempLine;
    fileData setting;
    bool isDone = false;

    if (request.query.size == 1){
        while (getline(file, tempLine)) { // SPRINT
            if (tempLine == " " || tempLine.empty()) {
                continue;
            }
            setting.getInfo(tempLine);
            if (setting.type == "#STACK") {
                isDone = true;
                Stack<string> currentValue = splitToStack(setting.data);
                cout << setting.name << ": " << currentValue << endl;
            }
        }
    }
    else if (request.query.size == 2) { // SPRINT name
        string name = request.query[1];
        fileData setting;
        while (getline(file, tempLine)){
            if (tempLine == " " || tempLine.empty()) continue;

            setting.getInfo(tempLine);
            if (setting.name == name && setting.type == "#STACK"){
                isDone = true;
                Stack<string> currentValue = splitToStack(setting.data);
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

void stackPush(const request& request){ //SPUSH name value

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

        if (setting.name == name && !isDone && setting.type == "#STACK"){
            isDone = true;
            Stack<string> currVar = splitToStack(setting.data);
            currVar.push(value);
            tempLine = setting.type + ';' + setting.name + ';' + unSplitStack(currVar);
            currVar.clear();
            buffer.push_back(tempLine);
        }
        else {
            buffer.push_back(tempLine);
        }
    }

    if (isDone == false){
        tempLine = "#STACK;" + name + ';' + value;
        buffer.push_back(tempLine);
    }
    file.close();
    file.open(request.file, ios::out);

    for (size_t i = 0; i < buffer.size; i++) {
        file << buffer[i] << endl;
    }
    file.close();
}


void stackPop(const request& request){ // SPOP name

    fstream file(request.file, ios::in);

    if (request.query.size != 2) {
        throw runtime_error("Wrong command syntax");
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
        if (setting.name == name && !isDone && setting.type == "#STACK"){
            isDone = true;
            Stack<string> currentValue = splitToStack(setting.data);
            currentValue.pop();
            tempLine = setting.type + ';' + setting.name + ';' + unSplitStack(currentValue);
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


void stackGet(const request& request){ //SGET name

    ifstream file(request.file, ios::in);
    if (request.query.size != 2) {
        throw runtime_error("Incorrect query");
    }
    string name = request.query[1];
    string tempLine;
    fileData setting;
    bool isDone = false;
    while (getline(file, tempLine)){ //проверяем все существующие переменные
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }
        setting.getInfo(tempLine);
        if (setting.name == name && setting.type == "#STACK"){ //если такая переменная существует
            isDone = true; //закрываем защёлку
            Stack<string> currentValue = splitToStack(setting.data); //определяем реальную переменную этого Типа данных
            cout << currentValue.getLast() << endl;
            currentValue.clear();
            break;
        }
    }
    if (!isDone){
        throw runtime_error("Incorrect name");
    }
}