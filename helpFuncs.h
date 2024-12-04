#ifndef HELPFUNCS_H
#define HELPFUNCS_H

#include <fstream>
#include "Structures/arr.h"
using namespace std;
struct request{
    arr<string> query;
    string file;
};

enum commands{
    MPUSH, MDEL, MGET, MPRINT, MSIZE,
    SPUSH, SPOP, SGET, SPRINT,
    LPUSH, LDEL, LGET, LPRINT,
    QPUSH, QPOP, QGET, QPRINT,
    HSET, HGET, HDEL, HPRINT,
    TINSERT, TCOMPLETE, TSEARCH, TPRINT
};

enum structures{
    Array,
    list,
    MYQueue,
    stack,
    hashmap,
    tree
};

struct fileData{
    string type;
    string name;
    string data;

    fileData () = default;
    fileData (string t, string n, string d) : type(t), name(n), data(d) {};

    void getInfo(const string &input) {
        arr<string> split;
        split = splitToArr(input, ';');
        if(split.size != 3 || split[0][0] != '#') {
            throw runtime_error("fileData error");
        }
        this->type = split[0];
        this->name = split[1];
        this->data = split[2];
    }
};

bool isFileExist(const string& fileName);
bool isItNumber(const string& str);
#endif //HELPFUNCS_H
