#ifndef LISTCOMMANDS_H
#define LISTCOMMANDS_H

#include "../lab_1.h"
#include "../helpFuncs.h"

using namespace std;

void printList(const request& request);
void listPush(const request& request);
void listDel(const request& request);
void listGet(const request& request);

#endif
