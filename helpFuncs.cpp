#include "helpFuncs.h"

commands commandRequest(const string& request){
    if (request == "MPUSH") return MPUSH;
    if (request == "MDEL") return MDEL;
    if (request == "MGET") return MGET;
    if (request == "MPRINT") return MPRINT;
    if (request == "MSIZE") return MSIZE;

    if (request == "SPUSH") return SPUSH;
    if (request == "SPOP") return SPOP;
    if (request == "SGET") return SGET;
    if (request == "SPRINT") return SPRINT;

    if (request == "QPUSH") return QPUSH;
    if (request == "QPOP") return QPOP;
    if (request == "QGET") return QGET;
    if (request == "QPRINT") return QPRINT;

    if (request == "LPUSH") return LPUSH;
    if (request == "LDEL") return LDEL;
    if (request == "LGET") return LGET;
    if (request == "LPRINT") return LPRINT;

    if (request == "HSET") return HSET;
    if (request == "HDEL") return HDEL;
    if (request == "HGET") return HGET;
    if (request == "HPRINT") return HPRINT;

    if (request == "TINSERT") return TINSERT;
    if (request == "TDEL") return TDEL;
    if (request == "TGET") return TGET;

    throw runtime_error("This command isn't exist");
}

structures structRequest(const char& input){
    if (input == 'M') return Array;
    if (input == 'L') return list;
    if (input == 'Q') return Queue;
    if (input == 'S') return stack;
    if (input == 'H') return hashmap;
    if (input == 'T') return Tree;


    throw runtime_error("This structure is not exist");

}

structures getType(const string& typeInFile){
    if (typeInFile == "#ARRAY") return Array;
    if (typeInFile == "#LIST") return list;
    if (typeInFile == "#QUEUE") return Queue;
    if (typeInFile == "#STACK") return stack;
    if (typeInFile == "#HASHMAP") return hashmap;
    if (typeInFile == "#TREE") return Tree;
    throw runtime_error("This structure isn't exist");
}

request getRequest(int argc, char *argv[] ){
    request output;
    for (int i = 0; i < argc; ++i){
        if (static_cast<string>(argv[i]) == "--file") {
            //если после флага ничего нет || если после флага другой флаг
            if (i + 1 == argc || argv[i + 1][0] == '-') { //Если первое условие выполняется - второе не приведёт к ошибке т.к. не будет проверяться
                throw runtime_error(("Error: empty query.\n Specify what to execute"));
            }
            output.file = argv[i + 1];
            continue;
        }
        if (static_cast<string>(argv[i]) == "--query") {
            if (i + 1 == argc || argv[i + 1][0] == '-') { //если после флага ничего нет || если после флага другой флаг
                throw runtime_error(("Error: empty query.\n Specify what to execute"));
            }
            output.query = splitToArr(argv[i + 1]);
        }
    }
    return output;
}

bool isFileExist(const std::string& fileName){
    ifstream file(fileName);
    if(!file.is_open()) return false;
    file.close();
    return true;
}

bool isItNumber(const string& str) {
    for (auto ch : str) {
        if (!isdigit(ch)) return false;
    }
    return true;
}