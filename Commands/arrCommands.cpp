#include "arrCommands.h"
#include "../Structures/arr.h"

void sizeArr(const request& request) {// MSIZE name
    ifstream file(request.file, ios::in);
    string name = request.query[1];
    string tempLine;
    fileData setting;
    if (request.query.size == 2) {
        while (getline(file, tempLine)) {
            if (tempLine == " " || tempLine.empty()) {
                continue;
            }
            setting.getInfo(tempLine);

            if (name == setting.name && setting.type == "#ARRAY") {
                arr<string> values = splitToArr(splitToArr(tempLine, ';')[2]);
                cout << setting.name << " size: " << values.size << endl;
            }
        }
    } else {
        throw runtime_error("Incorrect query");
    }
    file.close();
}

void printArr(const request& request){
    ifstream file(request.file, ios::in);
    string tempLine;
    if (request.query.size == 1){// вывести весь файл MPRINT
        fileData setting;
        while (getline(file, tempLine)) {
            if (tempLine == " " || tempLine.empty()) {
                continue;
            }
            setting.getInfo(tempLine);
            if (setting.type == "#ARRAY") {
                arr<string> currentValues = splitToArr(setting.data);
                cout << setting.name << ": " << currentValues << endl;
            }

        }
    }
    else if (request.query.size == 2) { //вывести конкретную переменную MPRINT name
        string name = request.query[1];
        fileData setting;
        bool isDone = false;
        while (getline(file, tempLine)){
            if (tempLine == " " || tempLine.empty()) {
                continue;
            }
            setting.getInfo(tempLine);

            if (setting.name == name && setting.type == "#ARRAY"){
                isDone = true;
                arr<string> currentValues = splitToArr(setting.data);
                cout << setting.name << ": " << currentValues << endl;
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

void arrPush(const request& request){//по индексу - MPUSH name index value; в конец - MPUSH name value
    // для того чтобы изменить элемент по индексу - MPUSH REPLACE name index value
    fstream file(request.file, ios::in);
    string name, value, tempLine;
    int index;
    fileData setting;

    if (request.query.size == 3) {
        name = request.query[1];
        index = -1;
        value = request.query[2];
    }
    else if (request.query.size == 4){
        name = request.query[1];
        index = stoi(request.query[2]);
        value = request.query[3];
    } else if (request.query.size == 5 && request.query[1] == "REPLACE"){
        name = request.query[2];
        index = stoi(request.query[3]);
        value = request.query[4];
    }
    else {
        throw runtime_error("Incorrect query");
    }

    bool isDone = false;
    arr<string> buffer;
    arr<string> currentValues;

    while (getline(file, tempLine)){
        if (tempLine == " " || tempLine.empty()) continue;
        setting.getInfo(tempLine);
        if (setting.name == name && setting.type == "#ARRAY" && request.query[1] == "REPLACE") {
            isDone = true;
            currentValues = splitToArr(setting.data);
            currentValues[index] = value;
            tempLine = setting.type + ';' + setting.name + ';' + unsplit(currentValues);
            buffer.push_back(tempLine);
        }
        else if (setting.name == name && !isDone && setting.type == "#ARRAY"){
            isDone = true; //закрываем защёлку
            currentValues = splitToArr(setting.data);
            currentValues.push_back(value);

            if (currentValues.size - 1 != index && index != -1){
                string tmp;//третий стакан
                for(size_t i = currentValues.size - 1; i > index; --i){
                    tmp = currentValues.data[i];
                    currentValues.data[i] = currentValues.data[i - 1];
                    currentValues.data[i - 1] = tmp;
                }
            }
            tempLine = setting.type + ";" + setting.name + ';' + unsplit(currentValues);
            buffer.push_back(tempLine);
        }
        else {
            buffer.push_back(tempLine);
        }
    }
    if (isDone == false){
        if (index != 0 && index != -1){//индекс может быть только 0 или -1
            throw runtime_error("Wrong index");
        }
        tempLine = "#ARRAY;" + name + ';' + value;//превращаем переменную в текст
        buffer.push_back(tempLine);
    }
    file.close();
    file.open(request.file, ios::out);

    for (size_t i = 0; i < buffer.size; i++) {
        file << buffer.data[i] << endl;
    }
    file.close();

}

void arrDel(const request& request){//MDEL name index

    fstream file(request.file, ios::in);
    if (request.query.size != 3 || !isItNumber(request.query[2])) {
        throw runtime_error("Incorrect query");
    }

    string name = request.query[1]; //из какого массива удалять
    size_t index = stoi(request.query[2]); //с какой позиции
    string tempLine; //считываемая строка с файла
    fileData setting;
    bool isDone = false;
    arr<string> buffer;

    while (getline(file, tempLine)){ //проверяем все существующие переменные
        if (tempLine == " " || tempLine.empty()) continue;
        setting.getInfo(tempLine);

        if (setting.name == name && !isDone && setting.type == "#ARRAY"){ //если такая переменная существует
            isDone = true; //закрываем защёлку
            arr<string> currentValues = splitToArr(setting.data); //определяем реальную переменную этого Типа данных
            currentValues.del(index);//удаление
            tempLine = setting.type + ";" + setting.name + ';' + unsplit(currentValues);//превращаем переменную в текст
            if (currentValues.size == 0) {
                tempLine = "";
            }
            buffer.push_back(tempLine);
        }
        else {
            buffer.push_back(tempLine);
        }
    }
    file.close();

    if (isDone == false){
        cout << "Incorrect array" << endl;
    }
    else{
        file.open(request.file, ios::out);

        for (size_t i = 0; i < buffer.size; i++) {
            file << buffer.data[i] << endl;
        }
        file.close();
    }
}

void arrGet(const request& request){//HGET name index

    fstream file(request.file, ios::in);
    if (request.query.size != 3 || !isItNumber(request.query[2])) {
        throw runtime_error("wrong command syntax");
    }
    string name = request.query[1];
    size_t index = stoi(request.query[2]);
    string tempLine;
    fileData setting;
    bool isDone = false;
    while (getline(file, tempLine)){ //проверяем все существующие переменные
        if (tempLine == " " || tempLine.empty()) {
            continue;
        }

        setting.getInfo(tempLine);
        if (setting.name == name && setting.type == "#ARRAY") { //если такая переменная существует
            isDone = true;
            arr<string> currentValues = splitToArr(setting.data); //определяем реальную переменную этого Типа данных
            if (index < currentValues.size) {
                cout << currentValues[index] << endl;
            }
            else {
                cout << "Incorrect index" << endl;
            }
            break;
        }
    }
    if (isDone == false) {
        cout << "Incorrect name array" << endl;
    }
}