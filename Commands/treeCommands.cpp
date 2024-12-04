#include "treeCommands.h"

#include "../Structures/ComplTree.h"

void treeInsert(const request& request) {// TINSERT name value

    fstream file(request.file, ios::in);

    if (request.query.size != 3) {
        throw runtime_error("Incorect query");
    }
    string name = request.query[1];
    int value = stoi(request.query[2]);

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
            CBTree currentValues = fromString(setting.data);
            currentValues.accept(value, currentValues.root);
            tempLine = setting.type + ";" + setting.name + ';' + treeToString(currentValues.root);
            buffer.push_back(tempLine);
        }
        else {
            buffer.push_back(tempLine);
        }
    }
    if (!isDone){
        tempLine = "#TREE;" + name + ';' + to_string(value) + ",";
        buffer.push_back(tempLine);
    }
    file.close();

    file.open(request.file, ios::out);

    for (size_t i = 0; i < buffer.size; i++) {
        file << buffer[i] << endl;
    }
    file.close();

}
