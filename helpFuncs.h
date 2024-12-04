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

    void getInfo(const string &input);
};

bool isFileExist(const string& fileName);
bool isItNumber(const string& str);
#endif //HELPFUNCS_H
