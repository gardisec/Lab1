#include "lab_1.h"

int main(int argc, char *argv[]) {
    try {
        request request = getRequest(argc, argv);
        if (argc == 1){
            throw runtime_error("Nothing arguments.");
        }
        if (request.query.size == 0){
            throw runtime_error("Query of request is empty");
        }
        structures structOfReq = structRequest(request.query[0][0]); //определяем по букве структуру
        if (!isFileExist(request.file) || request.file.empty()) {
            //проверяем доступ указанного файла/указан ли файл
            throw runtime_error("Incorrect file name, you must create file");
        }

        switch (structOfReq) {
            case Array:
                switch (commandRequest(request.query[0])) {
                    case MPUSH:
                        arrPush(request);
                        break;
                    case MDEL:
                        arrDel(request);
                        break;
                    case MGET:
                        arrGet(request);
                        break;
                    case MPRINT:
                        printArr(request);
                        break;
                    case MSIZE:
                        sizeArr(request);
                        break;
                    default:
                        throw runtime_error("Invalid array command");
                }
                break;

            case stack:
                switch (commandRequest(request.query[0])) {
                    case SPUSH:
                        stackPush(request);
                        break;
                    case SPOP:
                        stackPop(request);
                        break;
                    case SGET:
                        stackGet(request);
                        break;
                    case SPRINT:
                        printStack(request);
                        break;
                    default:
                        throw runtime_error("Invalid stack command");
                }
                break;

            case Queue:
                switch (commandRequest(request.query[0])) {
                    case QPUSH:
                        queuePush(request);
                        break;
                    case QPOP:
                        queuePop(request);
                        break;
                    case QGET:
                        queueGet(request);
                        break;
                    case QPRINT:
                        printQueue(request);
                        break;
                    default:
                        throw runtime_error("Invalid queue command");
                }
                break;

            case list:
                switch (commandRequest(request.query[0])) {
                    case LPUSH:
                        listPush(request);
                        break;
                    case LDEL:
                        listDel(request);
                        break;
                    case LGET:
                        listGet(request);
                        break;
                    case LPRINT:
                        printList(request);
                        break;
                    default:
                        cout << "Invalid list command" << endl;
                }
                break;

            case hashmap:
                switch (commandRequest(request.query[0])) {
                    case HSET:
                        hashPush(request);
                        break;
                    case HDEL:
                        hashDel(request);
                        break;
                    case HGET:
                        hashGet(request);
                        break;
                    case HPRINT:
                        printHash(request);
                        break;
                    default:
                        cout << "Invalid hashmap command" << endl;
                }
                break;

            case Tree:
                switch (commandRequest(request.query[0])) {
                    case TINSERT:
                        treeInsert(request);
                    break;
                    /*case TDEL:
                        treeDel(request);
                    break;
                    case TGET:
                        treeGet(request);
                    break;*/
                    default:
                        cout << "Invalid Tree command" << endl;
                }
                break;
        }
    }
    catch (exception &ex) {
        cout << ex.what() << endl;
        return -1;
    }
}