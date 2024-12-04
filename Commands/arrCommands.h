#ifndef ARRCOMMANDS_H
#define ARRCOMMANDS_H

#include "../lab_1.h"
#include "../helpFuncs.h"
#include <fstream>

using namespace std;

void sizeArr(const request& request);
void printArr(const request& request);
void arrPush(const request& request);
void arrDel(const request& request);
void arrGet(const request& request);

#endif
