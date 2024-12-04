#include "listCommands.h"
#include "../Structures/list.h"

void printList(const request& request){
    ifstream file(request.file);
    string tempLine;
    bool isDone = false;
    fileData setting;

    if (request.query.size == 1){

        while (getline(file, tempLine)) {//LPRINT
            if (tempLine == " " || tempLine.empty()) continue;
            setting.getInfo(tempLine);
            if (setting.type == "#LIST") {
                isDone = true;
                List<string> currentValue = splitToList(setting.data);
                cout << setting.name << ": " << currentValue << endl;
            }
        }
    }
    else if (request.query.size == 2) { // LPRINT name
        string name = request.query[1];


        while (getline(file, tempLine)){
            if (tempLine == " " || tempLine.empty()) {
                continue;
            }
            setting.getInfo(tempLine);

            if (setting.name == name && setting.type == "#LIST"){
                isDone = true; //закрываем защёлку
                List<string> currVar = splitToList(setting.data);
                cout << setting.name << " = " << currVar << endl;
            }
        }

    }
    if (isDone == false){
        throw runtime_error("Incorrect name or not data");
    }
    file.close();
}

void listPush(const request& request){// LPUSH HEAD/TAIL name value

    fstream file(request.file, ios::in);

    if (request.query.size != 4){
        throw runtime_error("Incorrect query");
    }
    string name = request.query[2];

    if (request.query[1] != "HEAD" && request.query[1] != "TAIL") {
        throw runtime_error("Incorrect query (second word must be HEAD/TAIL)");
    }
    string value = request.query[3];
    string tempLine;
    fileData setting;
    arr<string> buffer;
    bool isDone = false;

    while (getline(file, tempLine)){
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }

        setting.getInfo(tempLine);
        if (setting.name == name && !isDone && setting.type == "#LIST"){
            isDone = true;
            List<string> currentValue = splitToList(setting.data);
            if (request.query[1] == "HEAD"){
                currentValue.headInsert(value);
            }
            else {
                currentValue.backInsert(value);
            }
            tempLine = setting.type + ";" + setting.name + ';' + unSplitList(currentValue);//превращаем переменную в текст
            buffer.push_back(tempLine);
        }
        else {
            buffer.push_back(tempLine);
        }
    }
    if (!isDone){

        tempLine = "#LIST;" + name + ';' + value;
        buffer.push_back(tempLine);
    }
    file.close();
    file.open(request.file, ios::out);

    for (size_t i = 0; i < buffer.size; i++) {
        file << buffer[i] << endl;
    }
    file.close();
}


void listDel(const request& request){ //LDEL name value/HEAD/TAIL

    fstream file(request.file, ios::in);

    if (request.query.size != 3) {
        throw runtime_error("Wrong command syntax");
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
        if (setting.name == name && !isDone && setting.type == "#LIST"){
            isDone = true;
            List<string> currentValue = splitToList(setting.data);
            if (value == "HEAD") {
                currentValue.delFirst();
            }
            else if (value == "TAIL"){
                currentValue.delLast();
            }
            else {
                currentValue.del(value);
            }
            tempLine =setting.type + ";" + setting.name + ';' + unSplitList(currentValue);
            if (currentValue.first != nullptr){
                buffer.push_back(tempLine);
            }
        }
        else {
            buffer.push_back(tempLine);
        }
    }
    file.close();
    if (!isDone){
        throw runtime_error("Incorrect name");
    }
    file.open(request.file, ios::out);
    for (size_t i = 0; i < buffer.size; i++) {
        file << buffer[i] << endl;
    }
    file.close();
}


void listGet(const request& request){//LGET name value

    ifstream file(request.file);
    if (request.query.size != 3) {
        throw runtime_error("Incorrect query");
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
        if (setting.name == name && setting.type == "#LIST"){

            isDone = true;
            List<string> currentValue = splitToList(setting.data);
            if (currentValue.find(value)){
                cout << value << " is in " << name << endl;
            }
            else {
                cout << value << " isn't in the  " << name << endl;
            }
            break;
        }
    }
    if (!isDone){
        throw runtime_error("Incorrect name");
    }
}