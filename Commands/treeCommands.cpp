#include "treeCommands.h"

#include "../Structures/ComplTree.h"

void printTree(const request& request){
    fstream file(request.file, ios::in);
    string tempLine;
    fileData setting;
    if (request.query.size == 1) { //TPRINT
        while(getline(file, tempLine)) {
            setting.getInfo(tempLine);
            if (setting.type == "#TREE") {
                Tree* currVar = treeFromString(setting.data);
                currVar->printTree();

            }
        }
    } else if (request.query.size == 2) {//TPRINT name

        string name = request.query[1];
        bool isDone = false;
        while (getline(file, tempLine)){
            if (tempLine == " " || tempLine.empty()) {
                continue;
            }
            setting.getInfo(tempLine);
            if (setting.name == name && setting.type == "#TREE") {
                isDone = true;
                Tree* currVar = treeFromString(setting.data);
                currVar->printTree();
                break;
            }
        }
        if (!isDone){
            throw runtime_error("Incorrect name");
        }
    }
}


void treeInsert(const request& request) {// TINSERT name value

    fstream file(request.file, ios::in);

    if (request.query.size != 3) {
        throw runtime_error("Incorect query");
    }
    string name = request.query[1];
    string value = request.query[2];

    string tempLine;
    fileData setting;
    bool isDone = false;
    arr<string> buffer;

    while (getline(file, tempLine)){
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }
        setting.getInfo(tempLine);
        if (setting.name == name && !isDone && setting.type == "#TREE"){
            isDone = true;
            Tree* currentValues = treeFromString(setting.data);
            currentValues -> insertToTree(value);
            tempLine = setting.type + ";" + setting.name + ';' + treeToString(currentValues);
            buffer.push_back(tempLine);
            if (isCompleteBinaryTree(currentValues)){
                cout << "its complete binary tree" << endl;
            }
        }
        else {
            buffer.push_back(tempLine);
        }

    }
    if (!isDone){
        tempLine = "#TREE;" + name + ';' + value + ",";
        buffer.push_back(tempLine);
    }
    file.close();

    file.open(request.file, ios::out);

    for (size_t i = 0; i < buffer.size; i++) {
        file << buffer[i] << endl;
    }
    file.close();

}

void treeComplete(const request& request){//TCOMPLETE name
    fstream file(request.file, ios::in);

    if (request.query.size != 2) {
        throw runtime_error("Incorect query");
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
        if (setting.name == name && setting.type == "#TREE"){
            isDone = true;
            Tree* currentValues = treeFromString(setting.data);
            if (isCompleteBinaryTree(currentValues)){
                cout << name << " its complete binary tree" << endl;
            } else {
                cout << name << " its not complete binary tree" << endl;
            }
            break;
        }

    }
    if (!isDone){
        throw runtime_error("Tree is not found");
    }
    file.close();
}

void treeSearch(const request& request) {//TSEARCH name value
    fstream file(request.file, ios::in);

    if (request.query.size != 3) {
        throw runtime_error("Incorect query");
    }
    string name = request.query[1];
    string value = request.query[2];

    string tempLine;
    fileData setting;
    bool isDone = false;

    while (getline(file, tempLine)){
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }
        setting.getInfo(tempLine);
        if (setting.name == name && setting.type == "#TREE"){
            isDone = true;
            if (search(setting.data)){
                cout << value << " is in " << name << endl;
            } else {
                cout << value << " is not in " << name << endl;
            }
            break;
        }

    }
    if (!isDone){
        throw runtime_error("Tree is not found");
    }
    file.close();
}
