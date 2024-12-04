#include "hashCommands.h"
#include "../Structures/hashMap.h"

void printHash(const request& request) {
    fstream file(request.file, ios::in);
    string tempLine;
    fileData setting;
    if (request.query.size == 1) { //HPRINT
        while(getline(file, tempLine)) {
            setting.getInfo(tempLine);
            if (setting.type == "#HASHMAP") {
                hashMap currVar = hMFromStr(setting.data);
                cout << currVar.Get() << endl;
            }
        }
    } else if (request.query.size == 2) {//HPRINT name

        string name = request.query[1];
        bool isDone = false;
        while (getline(file, tempLine)){
            if (tempLine == " " || tempLine.empty()) {
                continue;
            }
            setting.getInfo(tempLine);
            if (setting.name == name && setting.type == "#HASHMAP") {
                isDone = true;
                hashMap currVar = hMFromStr(setting.data);
                cout << currVar.Get() << endl;
            }
        }
        if (!isDone){
            throw runtime_error("Incorrect name");
        }
    }
}

void hashPush(const request& request){// HSET name key value

    fstream file(request.file, ios::in);

    if (request.query.size != 4) {
        throw runtime_error("Incorect query");
    }
    string name = request.query[1];
    string key = request.query[2];
    string value = request.query[3];

    string tempLine;
    fileData setting;
    bool isDone = false;
    arr<string> buffer;

    while (getline(file, tempLine)){
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }
        setting.getInfo(tempLine);
        if (setting.name == name && !isDone && setting.type == "#HASHMAP"){
            isDone = true;
            hashMap currentValues = hMFromStr(setting.data);
            currentValues.insert(key, value);
            tempLine = setting.type + ";" + setting.name + ';' + strFromHM(currentValues);
            buffer.push_back(tempLine);
        }
        else {
            buffer.push_back(tempLine);
        }
    }
    if (!isDone){
        hashMap newVar;
        newVar.insert(key, value);
        tempLine = "#HASHMAP;" + name + ';' + strFromHM(newVar);
        buffer.push_back(tempLine);
    }
    file.close();

    file.open(request.file, ios::out);

    for (size_t i = 0; i < buffer.size; i++) {
        file << buffer[i] << endl;
    }
    file.close();

}


void hashDel(const request& request){//HDEL name key

    fstream file(request.file, ios::in);

    if (request.query.size != 3) {
        throw runtime_error("Incorrect query");
    }
    string name = request.query[1];
    string key = request.query[2];

    string tempLine;
    fileData setting;
    arr<string> buffer;
    bool isDone = false;

    while (getline(file, tempLine)){
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }

        setting.getInfo(tempLine);
        if (setting.name == name && setting.type == "#HASHMAP"){
            isDone = true;
            hashMap currentValue = hMFromStr(setting.data);
            currentValue.del(key);
            tempLine = setting.type + ";" + setting.name + ';' + strFromHM(currentValue);

            if (currentValue.pairCount != 0){
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


void hashGet(const request& request){// HGET name key

    ifstream file(request.file);

    if (request.query.size != 3) {
        throw runtime_error("Incorrect query");
    }
    string name = request.query[1];
    string key = request.query[2];

    string tempLine;
    fileData setting;
    bool isDone = false;

    while (getline(file, tempLine)) {
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }
        setting.getInfo(tempLine);
        if (setting.name == name && setting.type == "#HASHMAP") {

            isDone = true;
            hashMap currVar = hMFromStr(setting.data);
            if (currVar.pairCount == 0) {
                cout << "Empty :(" << endl;
            }
            else {
                cout << currVar.Get(key) << endl;
            }
            break;
        }
    }
    if (!isDone) {
        throw runtime_error("Incorrect name");
    }
}